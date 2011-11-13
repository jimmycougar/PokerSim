#include "seat.h"

Seat::Seat(Player* inPlayer, Card* inCard1, Card* inCard2, int inStackSize) :
	player(inPlayer),
	card1(inCard1),
	card2(inCard2),
	stackSize(inStackSize)
{
	folded = false;
}

Seat::~Seat() 
{

}

