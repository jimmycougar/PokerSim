#include <iostream>
#include <stdio.h>
#include <exception>
#include <vector>

#include "view/cardprinter.h"
#include "model/card.h"
#include "model/deck.h"
#include "model/seat.h"
#include "model/handstrength.h"

const char * CardPrinter::cardinalString[] = {
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
	"King",
	"Ace"};

const char * CardPrinter::suitString[] = {
	" of Hearts",
	" of Diamonds",
	" of Spades",
	" of Clubs"};

const char * CardPrinter::strengthString[] = {
	"%s high",
	"Pair of %ss",
	"Two pair: %ss up",
	"Three %ss",
	"Straight: %s high",
	"Flush: %s high",
	"Full house: %ss full",
	"Four %ss",
	"Straight flush: %s high" };

void CardPrinter::Print(Card * card)
{
	if(!card)
		return;

	std::cout << cardinalString[card->GetCardinal()] 
		<< suitString[card->GetSuit()] << std::endl;
}

void CardPrinter::PrintHandStrength(HandStrength * handStrength)
{
	int handType = handStrength->handVal.front();

	printf("%s\n", strengthString[handType]);
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

//void CardPrinter::PrintSeats(const std::vector<Seat*> &seats)
//{
//	std::cout << "Printing seats..." << std::endl; 
	//std::vector<Seat*>::const_iterator iter;
	
	//for(iter = seats.begin(); iter != seats.end(); iter++)
	//{
	//	std::cout<<"Player "<<(*iter)->player->GetFirstName()<<" "
	//		<<(*iter)->player->GetLastName()<<std::endl;

	//	Print((*iter)->card1);
	//	Print((*iter)->card2);
	//	std::cout<<"\n";
	//}
//}
