#include "regulator.h"

Regulator::Regulator()
{
	initCards();
	deck = new Deck(cards);	
}

Regulator::~Regulator()
{
	delete deck;
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

Deck * Regulator::GetDeck()
{
	return deck;
}

void Regulator::DealCards() 
{

}
