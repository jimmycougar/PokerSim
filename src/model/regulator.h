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
	void RegisterObserverAll(Observer * observer);
	void RegisterCardObserver(Observer * observer);
	void RegisterActionObserver(Observer * observer);
	void RegisterHandShowObserver(Observer * observer);
	void RegisterWinnerObserver(Observer * observer);

	// game state functions
	void AddPlayer(Player * player);
	void Simulate();
	
private:

	// notification functions
	void notifyAction(int seatNum, int bet);
	void notifyCardDealt(Card * card);
	void notifyHandShow(Seat * seat);
	void notifyWinner(Seat * seat, int potSize);

	// game-wide member functions
	void initCards();

	// hand specific member functions
	void beginHand();
	void dealCardsToPlayers();
	void dealCardsToBoard(int numCards);
	bool getPlayerActions();
	void showdown();
	void cleanupHand();

	// subscriber lists
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
	Table::iterator actionSeat;
	int currentBet;
	int potSize;
};

#endif // REGULATOR_H

