#ifndef SEAT_H
#define SEAT_H

class Player;
class Card;
class HandStrength;

class Seat
{

public:

	int seatNum;
	Player* player;
	Card* card1;
	Card* card2;
	int stackSize;
	int currentBet;
	HandStrength * hand;
};

#endif //SEAT_H

