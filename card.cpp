#include "card.h"

Card::Card(NUMBER inNum, SUIT inSuit) : 
	num(inNum),
	suit(inSuit)
{

}

Card::NUMBER Card::GetNumber() 
{
	return num;
}

Card::SUIT Card::GetSuit()
{
	return suit;
}

