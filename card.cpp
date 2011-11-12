#include "card.h"

const char * Card::CardinalString[] = { 
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

const char * Card::SuitString[] = {
	" of Hearts",
	" of Diamonds",
	" of Spades",
	" of Clubs"};

Card::Card()
{}

Card::Card(Cardinal inCardinal, Suit inSuit) : 
	cardinal(inCardinal),
	suit(inSuit)
{}

Card::Cardinal Card::GetCardinal() 
{
	return cardinal;
}

const char * Card::GetCardinalString()
{
	return CardinalString[cardinal];
}

Card::Suit Card::GetSuit()
{
	return suit;
}

const char * Card::GetSuitString()
{
	return SuitString[suit];
}

