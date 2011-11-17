#ifndef REGULATOR_H
#define REGULATOR_H

/*
 * This class defines the rules of Texas Holdem. It uses the other
 * objects in the model to implement the game.
 */

#include <vector>

#include "model/card.h"
#include "model/deck.h"
#include "model/seat.h"

class Player;

class Regulator
{
public:
	Regulator();
	~Regulator();

	Deck * GetDeck();
	std::vector<Seat*> GetSeats();
	void AddPlayer(Player * player);
	int GetPotSize();
	void DealCards();
	void Simulate(){}

	void BeginHand();
	void Notify();
	
private:
	void initCards();
	void initPlayers();
	void initSeats();
	void dealCardsToPlayers();
	int requestPlayerAction(const std::vector<Seat*> &seatPostions, int currentBetSize);
	void dealCardsToBoard(int numCards);

	Card cards[DECKSIZE];
	Deck * deck;
	Player * player1;
	Player * player2;
	Player * player3;
	Player * player4;
	Player * player5;
	Player * player6;
	Player * player7;
	Player * player8;
	Player * player9;
	Player * player10;	
	
	std::vector<Seat*> seats;
	int potSize;
};

#endif // REGULATOR_H

