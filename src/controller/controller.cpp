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
	CardPrinter::PrintDeck(deck);
	deck->Shuffle();

	CardPrinter::PrintDeck(deck);
	deck->Shuffle();
	CardPrinter::PrintDeck(deck);
	
	
	//TODO: check that blinds are in place
	//regulator.DealCards();
}

