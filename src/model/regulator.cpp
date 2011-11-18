#include "model/regulator.h"
#include "model/player.h"
#include "model/seat.h"
#include "model/handstrength.h"
#include "observer.h"

Regulator::Regulator()
{
	initCards();
	deck = new Deck(cards);
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

	Seat * seat = new Seat();
	seat->seatNum = seats.size();
	seat->player = newPlayer;
	seats.push_back(seat);
	RegisterObserverAll(newPlayer);
}


void Regulator::RegisterObserverAll(Observer * observer)
{
	RegisterCardObserver(observer);
	RegisterActionObserver(observer);
	RegisterHandShowObserver(observer);
	RegisterWinnerObserver(observer);
}

void Regulator::RegisterCardObserver(Observer * observer)
{
	cardObservers.push_back(observer);
}

void Regulator::RegisterActionObserver(Observer * observer)
{
	actionObservers.push_back(observer);
}

void Regulator::RegisterHandShowObserver(Observer * observer)
{
	handShowObservers.push_back(observer);
}

void Regulator::RegisterWinnerObserver(Observer * observer)
{
	winnerObservers.push_back(observer);
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
	
	// add everyone to be in the hand
	seatsInHand = seats;

	Table::iterator iter;
	
	// initialize seat's hand specific vars
	for(iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		(*iter)->currentBet = 0;
		(*iter)->card1 = 0;
		(*iter)->card2 = 0;
	}

	// setup the blinds
	iter = seatsInHand.begin();
	Seat * smallBlindSeat = *iter;
	++iter;
	Seat * bigBlindSeat = *iter;
	++iter;
	if(iter == seatsInHand.end())
		actionSeat = seatsInHand.begin();
	else
		actionSeat = iter;
	
	// post the blinds
	smallBlindSeat->currentBet = smallBlindSeat->player->PostBlind(smallBlind);
	bigBlindSeat->currentBet = bigBlindSeat->player->PostBlind(bigBlind);

	currentBet = bigBlind;

	deck->Shuffle();
	dealCardsToPlayers();

	}

// returns true if the hand should continue
bool Regulator::getPlayerActions()
{
	// get player actions until largest bet has been called by all remaining players
	while((*actionSeat)->currentBet < currentBet || currentBet == 0)
	{
		// ask the player what he wants to do
		int bet = (*actionSeat)->player->GetPlayerAction(currentBet);
		
		// notify all of the players about what this player did
		notifyAction((*actionSeat)->seatNum, bet);

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
		
		// handle action after button seat
		if(actionSeat == seatsInHand.end())
		{
			if(currentBet == 0)
				// if it checked around
				break;
			else
				// there is more action to be played; action is on first player
				actionSeat = seatsInHand.begin();
		}
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

void Regulator::notifyAction(int seatNum, int bet)
{
	for(ObserverList::iterator iter = actionObservers.begin(); iter != actionObservers.end(); ++iter)
		(*iter)->notifyAction(seatNum, bet);
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
		// these HandStrengths will be deleted here for losers, and in cleanupHand() for winners
		(*iter)->hand = new HandStrength(hand);
		handList.push_back(*(*iter)->hand);
		notifyHandShow(*iter);
	}

	// determine the best hand
	handList.sort();
	HandStrength topHand = handList.back();

	// remove any hands that are not the best
	for(Table::iterator iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		if(*((*iter)->hand) < topHand)
		{
			delete (*iter)->hand;
			seatsInHand.erase(iter--);
		}
	}
}

void Regulator::notifyHandShow(Seat * seat)
{
	for(ObserverList::iterator iter = handShowObservers.begin(); iter != handShowObservers.end(); ++iter)
		(*iter)->notifyHandShow(seat->seatNum, seat->card1, seat->card2, seat->hand);
}

void Regulator::notifyWinner(Seat * seat, int potSize)
{
	for(ObserverList::iterator iter = winnerObservers.begin(); iter != winnerObservers.end(); ++iter)
		(*iter)->notifyWinner(seat->seatNum, seat->hand, potSize);
}

void Regulator::cleanupHand()
{
	// any players still in the hand at this point are winners
	int share = potSize / seatsInHand.size();
	unsigned int winners = 0;
	for(Table::iterator iter = seatsInHand.begin(); iter != seatsInHand.end(); ++iter)
	{
		int winnings = share;
		// adjust for split pots
		if((potSize % seatsInHand.size()) > winners)
			winnings += 1;

		// give the chips to the winner
		(*iter)->stackSize += winnings;
		
		// notify observers
		notifyWinner(*iter, winnings);
		
		// cleanup the HandStrength that was allocated in showdown()
		delete (*iter)->hand;

		++winners;
	}

	// move the button
	Seat * smallBlindSeat = seats.front();
	seats.pop_front();
	seats.push_back(smallBlindSeat);

}

void Regulator::dealCardsToBoard(int numCards)
{
	for(int i=0; i<numCards; ++i)
	{
		Card * card = deck->Pop();
		board.push_back(card);
		notifyCardDealt(card);
	}
}

void Regulator::notifyCardDealt(Card * card)
{
	for(ObserverList::iterator iter = cardObservers.begin(); iter != cardObservers.end(); ++iter)
		(*iter)->notifyCard(card);
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

