#include "model/regulator.h"
#include "model/player.h"

Regulator::Regulator()
{
	initCards();
	deck = new Deck(cards);	

	initPlayers();
	initSeats();
}

Regulator::~Regulator()
{
	delete deck;
	delete player1;
	delete player2;
	delete player3;
	delete player4;
	delete player5;
	delete player6;
	delete player7;
	delete player8;
	delete player9;
	delete player10;

	std::vector<Seat*>::iterator iter;
	for(iter = seats.begin(); iter < seats.end(); iter++)
	{
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

}

void Regulator::initPlayers() 
{
	player1 = new Player("Joe", "Smith", 2000, 300);
	player2 = new Player("Katie", "Bradshaw", 1500, 200);
	player3 = new Player("Kevin", "Peterson", 5000, 300);
	player4 = new Player("Jimmy", "Thomas", 4500, 250);
	player5 = new Player("Jane", "Doe", 1500, 150);
	player6 = new Player("David", "Hammer", 8000, 300);
	player7 = new Player("Jackie", "Diamond", 3300, 300);
	player8 = new Player("Blah", "LastName", 4900, 300);
	player9 = new Player("John", "Crap", 2000, 200);
	player10 = new Player("Herro", "Goodbye", 2900, 300);
}

void Regulator::initSeats() 
{
	Seat* seat1 = new Seat(player1, 0, 0, player1->GetStackSize());
	Seat* seat2 = new Seat(player2, 0, 0, player2->GetStackSize());
	Seat* seat3 = new Seat(player3, 0, 0, player3->GetStackSize());
	Seat* seat4 = new Seat(player4, 0, 0, player4->GetStackSize());
	Seat* seat5 = new Seat(player5, 0, 0, player5->GetStackSize());
	Seat* seat6 = new Seat(player6, 0, 0, player6->GetStackSize());
	Seat* seat7 = new Seat(player7, 0, 0, player7->GetStackSize());
	Seat* seat8 = new Seat(player8, 0, 0, player8->GetStackSize());
	Seat* seat9 = new Seat(player9, 0, 0, player9->GetStackSize());
	Seat* seat10 = new Seat(player10, 0, 0, player10->GetStackSize());

	seats.push_back(seat1);
	seats.push_back(seat2);
	seats.push_back(seat3);
	seats.push_back(seat4);
	seats.push_back(seat5);
	seats.push_back(seat6);
	seats.push_back(seat7);
	seats.push_back(seat8);
	seats.push_back(seat9);
	seats.push_back(seat10);
}

void Regulator::BeginHand() 
{
	std::vector<Seat*>::iterator iter;
	int currentPotSize, bigBlind, smallBlind = 0;

	for(iter = seats.begin(); iter != seats.end(); iter++)
	{
		if(currentPotSize == 0)
		{
			smallBlind = (*iter)->player->PostSmallBlind();
			currentPotSize++;
		} 
		else if(currentPotSize == 1)
		{
			bigBlind = (*iter)->player->PostBigBlind();
			currentPotSize++;
		} 
		else
		{
			break;
		}
	}

	std::vector<Seat*> preFlopSeatOrder(seats);
	preFlopSeatOrder.push_back(preFlopSeatOrder.front());	//move small blind to back
	preFlopSeatOrder.push_back(preFlopSeatOrder.front());	//move big blind to back

	dealCardsToPlayers();
	currentPotSize += requestPlayerAction(preFlopSeatOrder, bigBlind);

	dealCardsToBoard(3);
	currentPotSize += requestPlayerAction(seats, currentPotSize);

	dealCardsToBoard(1);
	currentPotSize += requestPlayerAction(seats, currentPotSize);

	dealCardsToBoard(1);
	currentPotSize += requestPlayerAction(seats, currentPotSize);

	//Ask players to show cards and find winner
}

void Regulator::Notify()
{
	//go through our list of observers and call all notify functions
}

void Regulator::dealCardsToBoard(int numCards)
{

}

int Regulator::requestPlayerAction(const std::vector<Seat*> &seatPositions, int currentBetSize)
{
	std::vector<Seat*>::const_iterator iter;
	int originalBetSize = currentBetSize;

	for(iter = seatPositions.begin(); iter != seatPositions.end(); iter++)
	{
		int playerBetSize = (*iter)->player->GetPlayerAction(originalBetSize);

		if(playerBetSize > originalBetSize)
		{
			//TODO: make sure raise amount is valid
		}

		//regulator needs to handle player action
	}

	return 0;
}


void Regulator::dealCardsToPlayers()
{
	std::vector<Seat*>::iterator iter;
	
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

std::vector<Seat*> Regulator::GetSeats()
{
	return seats;
}

int Regulator::GetPotSize() 
{
	return potSize;
}
