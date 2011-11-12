#include <iostream>

#include "model/deck.h"
#include "model/card.h"

int main()
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
		std::cout << card->GetCardinalString() << card->GetSuitString() << std::endl;
	}
			
	return 0;
}
