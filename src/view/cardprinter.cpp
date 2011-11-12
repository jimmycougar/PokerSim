#include <iostream>

#include "view/cardprinter.h"
#include "model/card.h"

const char * CardPrinter::cardinalString[] = {
	"Ace",
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Jack",
	"Queen",
	"King"};

const char * CardPrinter::suitString[] = {
	" of Hearts",
	" of Diamonds",
	" of Spades",
	" of Clubs"};

void CardPrinter::Print(Card * card)
{
	if(!card)
		return;

	std::cout << cardinalString[card->GetCardinal()] 
		<< suitString[card->GetSuit()] << std::endl;
}

