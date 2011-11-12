#include "card.h"

Card::Card(Cardinal inCardinal, Suit inSuit) : 
	cardinal(inCardinal),
	suit(inSuit)
{

}

Card::Cardinal Card::GetCardinal() 
{
	return cardinal;
}

Card::Suit Card::GetSuit()
{
	return suit;
}

