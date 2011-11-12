#include "deck.h"
#include "card.h"

Deck::Deck(Card* inCardInstance) 
{
	cardInstance = inCardInstance;
	nextCard = 0;
	
	for(int i=0; i<DECKSIZE; i++)
	{
		cards[i] = cardInstance+i;
	}
}

Deck::~Deck()
{
	
}

void Deck::Shuffle() 
{

}

Card* Deck::Pop() 
{
	if (nextCard >= DECKSIZE)
		return 0;
	return cards[nextCard++];
}

