#ifndef REGULATOR_H
#define REGULATOR_H

/*
 * This class defines the rules of Texas Holdem. It uses the other
 * objects in the model to implement the game.
 */

#include <list>

#include "model/card.h"
#include "model/deck.h"

class Player;
class Seat;

typedef std::list<Seat*> Table;
typedef std::list<Card*> CardList;

class Regulator
{
public:
	Regulator();
	~Regulator();

	Deck * GetDeck();
	Table GetSeats();
	void AddPlayer(Player * player);
	int GetPotSize();
	void Simulate();
	
private:
	// game-wide member functions
	void initCards();

	// hand specific member functions
	void beginHand();
	void dealCardsToPlayers();
	void dealCardsToBoard(int numCards);
	bool getPlayerActions();
	void notifyPlayers(int seatNum, int bet);
	void showdown();
	void cleanupHand();

	// game-wide member vars
	Card cards[DECKSIZE];
	Deck * deck;
	int numPlayers;
	Table seats;

	// hand specific member vars
	Table seatsInHand;
	CardList board;
	Table::iterator actionSeat;
	int currentBet;
	int potSize;
};

#endif // REGULATOR_H

