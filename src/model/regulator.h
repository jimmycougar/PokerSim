#ifndef REGULATOR_H
#define REGULATOR_H

/*
 * This class defines the rules of Texas Holdem. It uses the other
 * objects in the model to implement the game.
 */

#include "model/card.h"
#include "model/deck.h"

class Regulator
{
public:
	Regulator();
	~Regulator();

	Deck * GetDeck();

private:
	void initCards();

	Card cards[DECKSIZE];
	Deck * deck;
};

#endif // REGULATOR_H

