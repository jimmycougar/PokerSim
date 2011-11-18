#include <iostream>
#include <stdio.h>
#include <exception>
#include <vector>

#include "view/cardprinter.h"
#include "model/card.h"
#include "model/deck.h"
#include "model/seat.h"
#include "model/handstrength.h"

using std::string;
using std::cout;

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

	cout << cardinalString[card->GetCardinal()] 
		<< suitString[card->GetSuit()];
}

void CardPrinter::PrintHandStrength(HandStrength * handStrength)
{
	HandStrength hand = *handStrength;
	int handType = hand.handVal.front();
	hand.handVal.pop_front();
	int handVal = hand.handVal.front();
	hand.handVal.pop_front();
	
	char buffer[256];
	sprintf(buffer, strengthString[handType], cardinalString[handVal]);
	cout << buffer;
	while(!hand.handVal.empty())
	{
		// debug line commented out
		//cout << " " << hand.handVal.front();
		hand.handVal.pop_front();
	}
	cout << std::endl;
}

void CardPrinter::PrintDeck(Deck * deck) 
{
	if(!deck)
	{
		throw std::exception();
	}

	cout << "\nPrinting deck...\n";
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
