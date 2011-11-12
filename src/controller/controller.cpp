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
	Card * card;
	while( (card = deck->Pop()) != 0)
	{
		CardPrinter::Print(card);
	}
}
