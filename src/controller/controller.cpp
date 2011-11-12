#include "controller/controller.h"
#include "model/deck.h"
#include "model/card.h"
#include "view/cardprinter.h"

Controller::Controller()
{
	Card cards[DECKSIZE];
	for(int i=0; i<NUMSUITS; ++i)
	{
		for(int j=0; j<NUMCARDINALS; ++j)
		{
			cards[i*NUMCARDINALS+j] = Card((Card::Cardinal)j, (Card::Suit)i);
		}
	}

	Deck deck(cards);
	
	Card * card;
	while( (card = deck.Pop()) != 0)
	{
		CardPrinter::Print(card);
	}
}
