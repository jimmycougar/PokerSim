#include "controller/controller.h"
#include "model/deck.h"
#include "view/cardprinter.h"

Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::Run()
{
	Deck * deck = regulator.GetDeck();
	deck->Shuffle();
	deck->Shuffle();
	
	
	//TODO: check that blinds are in place
	
	regulator.DealCards();
	CardPrinter::PrintSeats(regulator.GetSeats());
}

