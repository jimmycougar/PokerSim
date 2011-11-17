#include "model/regulator.h"
#include "model/player.h"
#include "model/seat.h"
#include "model/handstrength.h"

Regulator::Regulator()
{
	initCards();
	deck = new Deck(cards);
	numPlayers = 0;
}

Regulator::~Regulator()
{
	delete deck;

	for(Table::iterator iter = seats.begin(); iter != seats.end(); ++iter)
	{
		delete (*iter)->player;
		delete *iter;
	}
}

void Regulator::initCards()
{
	for(int i=0; i<NUMSUITS; ++i)
	{
		for(int j=0; j<NUMCARDINALS; ++j)
		{
			cards[i*NUMCARDINALS+j] = Card((Card::Cardinal)j, (Card::Suit)i);
		}
	}
}

void Regulator::AddPlayer(Player * newPlayer)
{
	if(newPlayer == NULL)
		return;

	Seat * seat;
	seat->seatNum = numPlayers++;
	seat->player = newPlayer;
	seats.push_back(seat);
}

void Regulator::Simulate()
{

	beginHand();

	if(getPlayerActions())
	{
		dealCardsToBoard(3);
		if(getPlayerActions())
		{
			dealCardsToBoard(1);
			if(getPlayerActions())
			{
				dealCardsToBoard(1);
				if(getPlayerActions())
				{
					showdown();
				}
			}
		}
	}
	cleanupHand();
}


void Regulator::beginHand() 
{
	if(seats.size() < 2)
		return;

	// these should be member variables that get set by controller
	int smallBlind = 1;
	int bigBlind = 2;

	// initialize hand specific variables
	potSize = 0;
	currentBet = 0;
	board.clear();
	seatsInHand.clear();
	
	Table::iterator iter;
	
	// initialize seat's hand specific vars
	for(iter = seats.begin(); iter != seats.end(); ++iter)
	{
		(*iter)->currentBet = 0;
		(*iter)->card1 = 0;
		(*iter)->card2 = 0;
	}

	// setup the blinds
	iter = seats.begin();
	Seat * smallBlindSeat = *iter;
	++iter;
	Seat * bigBlindSeat = *iter;
	++iter;
	if(iter == seats.end())
		actionSeat = seats.begin();
	else
		actionSeat = iter;
	
	// post the blinds
	smallBlindSeat->currentBet = smallBlindSeat->player->PostBlind(smallBlind);
	bigBlindSeat->currentBet = bigBlindSeat->player->PostBlind(bigBlind);

	currentBet = bigBlind;

	deck->Shuffle();
	dealCardsToPlayers();

	// add everyone to be in the hand
	seatsInHand = seats;
}

// returns true if the hand should continue
bool Regulator::getPlayerActions()
{
	// get player actions until largest bet has been called by all remaining players
	while((*actionSeat)->currentBet < currentBet)
	{
		// ask the player what he wants to do
		int bet = (*actionSeat)->player->GetPlayerAction(currentBet);
		
		// notify all of the players about what this player did
		notifyPlayers((*actionSeat)->seatNum, bet);

		if(bet < currentBet)
		{
			// player folded; move his current bet to the pot and remove him from the hand
			potSize += (*actionSeat)->currentBet;
			(*actionSeat)->stackSize -= (*actionSeat)->currentBet;
			// this removes the player and advances the iterator to the next item in the list
			actionSeat = seatsInHand.erase(actionSeat);
		}
		else
		{
			// player called or raised
			(*actionSeat)->currentBet = currentBet = bet;
			// get the next players action
			++actionSeat;
		}
		
		// wrap around
		if(actionSeat == seatsInHand.end())
			actionSeat = seatsInHand.begin();
	}

	// set the action on the player after the button
	actionSeat = seatsInHand.begin();

	// move the bets from the players' stacks to the pot
	for(Table::iterator iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		potSize += currentBet;
		(*iter)->stackSize -= currentBet;
		(*iter)->currentBet = 0;
	}

	currentBet = 0;

	// return whether the hand should continue
	return seatsInHand.size() > 1;
}

void Regulator::notifyPlayers(int seatNum, int bet)
{
	for(Table::iterator iter = seats.begin(); iter!= seats.end(); ++iter)
	{
		(*iter)->player->NotifyPlayerAction(seatNum, bet);
	}
}

void Regulator::showdown()
{
	std::list<HandStrength> handList;

	// add all the handlists up
	for(Table::iterator iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		CardList hand = board;
		hand.push_back((*iter)->card1);
		hand.push_back((*iter)->card2);
		*((*iter)->hand) = HandStrength(hand);
		handList.push_back(*((*iter)->hand));
	}

	// determine the best hand
	handList.sort();
	HandStrength topHand = handList.back();

	// remove any hands that are not the best
	for(Table::iterator iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		if(*((*iter)->hand) < topHand)
		{
			seatsInHand.erase(iter);
		}
	}
}

void Regulator::cleanupHand()
{

}

void Regulator::dealCardsToBoard(int numCards)
{

}

void Regulator::dealCardsToPlayers()
{
	std::list<Seat*>::iterator iter;
	
	Card* card;
	for(iter=seats.begin(); iter != seats.end(); iter++) 
	{
		card = deck->Pop();
		(*iter)->card1 = card;
	}

	for(iter=seats.begin(); iter != seats.end(); iter++)
	{
		card = deck->Pop();
		(*iter)->card2 = card;
	}
}

Deck * Regulator::GetDeck()
{
	return deck;
}

std::list<Seat*> Regulator::GetSeats()
{
	return seats;
}

int Regulator::GetPotSize() 
{
	return potSize;
}

