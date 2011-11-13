#ifndef SEAT_H
#define SEAT_H

#include "model/player.h"
#include "model/card.h"

class Seat
{

public:

	Seat(Player* inPlayer, Card* inCard1, Card* inCard2, int inStackSize);
	~Seat();

	Player* player;
	Card* card1;
	Card* card2;
	int stackSize;
	bool folded;

};
#endif //SEAT_H

