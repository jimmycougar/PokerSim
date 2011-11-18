#include <iostream>
#include <string>

#include "controller/controller.h"
#include "model/userplayer.h"
#include "model/aiplayer.h"

using std::string;
using std::cout;
using std::cin;

Controller::Controller(Observer * inView, Regulator * inRegulator) :
	view(inView),
	regulator(inRegulator)
{
	regulator->RegisterObserverAll(view);
}

Controller::~Controller()
{

}

void Controller::Run()
{
	// get options
	int numPlayers;
	cout << "Number of AI players: ";
	cin >> numPlayers;

	//regulator.AddPlayer(new UserPlayer(stackSize));
	for(int i=0; i<numPlayers; ++i)
	{
		regulator->AddPlayer(new AIPlayer(0));
	}


	regulator->Simulate();
}

