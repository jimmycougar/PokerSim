#include <iostream>
#include <string>

#include "controller/controller.h"
#include "model/userplayer.h"
#include "model/aiplayer.h"

using std::string;
using std::cout;
using std::cin;

Controller::Controller() :
	shutdown(false)
{

}

Controller::~Controller()
{

}

void Controller::processOutput()
{
}

void Controller::handleInput()
{
}

void Controller::Run()
{
	// get options
	int numPlayers;
	cout << "Number of AI players: ";
	cin >> numPlayers;
	int stackSize;
	cout << "Starting stack size: ";
	cin >> stackSize;

	//regulator.AddPlayer(new UserPlayer(stackSize));
	//for(int i=0; i<numPlayers; ++i)
	//{
//		regulator.AddPlayer(new AIPlayer(stackSize));
//	}

//	regulator.Simulate();
/*
	Card c1(Card::ACE, Card::SPADE);
	Card c2(Card::QUEEN, Card::HEART);
	Card c3(Card::TEN, Card::DIAMOND);
	Card c4(Card::ACE, Card::CLUB);
	Card c5(Card::JACK, Card::CLUB);
	Card c6(Card::KING, Card::SPADE);
	Card c7(Card::KING, Card::CLUB);
	Card c8(Card::KING, Card::DIAMOND);
	Card c9(Card::KING, Card::HEART);

	Card *cards1[5] = {&c1, &c4, &c6, &c7, &c8};
	Card *cards2[5] = {&c1, &c2, &c3, &c5, &c6};

	HandStrength hand1(cards1, 5);
	HandStrength hand2(cards2, 5);

	HandStrength * winner = &hand1;
	HandStrength * loser = &hand2;
	if( hand1 < hand2 )
	{
		winner = &hand2;
		loser = &hand1;
	}

	CardPrinter::PrintHandStrength(winner);
	std::cout << " beats \n";
	CardPrinter::PrintHandStrength(loser);
*/
	
	//TODO: check that blinds are in place
	
	//regulator.DealCards();
	//CardPrinter::PrintSeats(regulator.GetSeats());
}

