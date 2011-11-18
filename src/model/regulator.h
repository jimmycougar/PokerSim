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
class Observer;

typedef std::list<Seat*> Table;
typedef std::list<Card*> CardList;
typedef std::list<Observer*> ObserverList;

class Regulator
{
public:
	Regulator();
	~Regulator();

	// subscribe functions
	void RegisterObserver(Observer * observer);

	// game state functions
	void AddPlayer(Player * player);
	void Simulate();
	
private:

	// notification functions
	void notifyBlinds(Seat * smallBlindSeat, Seat * bigBlindSeat, int smallBlind, int bigBlind);
	void notifyAction(Seat * seat, int, int);
	void notifyCardDealt(Card * card);
	void notifyHandShow(Seat * seat);
	void notifyWinner(Seat * seat, int potSize);

	// game-wide member functions
	void initCards();

	// hand specific member functions
	bool beginHand();
	void dealCardsToPlayers();
	void dealCardsToBoard(int numCards);
	bool getPlayerActions();
	void showdown();
	void cleanupHand();

	// subscriber lists
	ObserverList blindObservers;
	ObserverList cardObservers;
	ObserverList actionObservers;
	ObserverList handShowObservers;
	ObserverList winnerObservers;

	// game-wide member vars
	Card cards[DECKSIZE];
	Deck * deck;
	Table seats;

	// hand specific member vars
	Table seatsInHand;
	CardList board;
	int currentBet;
	int potSize;
};

#endif // REGULATOR_H

