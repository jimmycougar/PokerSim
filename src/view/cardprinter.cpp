#include <iostream>
#include <exception>

#include "view/cardprinter.h"
#include "model/card.h"
#include "model/deck.h"

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

void CardPrinter::PrintDeck(Deck * deck) 
{
	if(!deck)
	{
		throw std::exception();
	}

	std::cout << "\nPrinting deck...\n";
	Card * card;
	while((card = deck->Pop()) != 0) 
	{
		Print(card);
	}
}
