#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "observer.h"

using std::string;

class Card;

class Player : public Observer
{
	
public:

	Player(string inFirstName, string inLastName, int inBankRoll);
	~Player();

	int PostBlind(int blindSize);
	string GetFirstName();
	string GetLastName();
	int GetPlayerAction(int betSize);
	virtual void notifyCard(Card * card);
	virtual void notifyAction(int seatNum, int betSize);

private:

	string firstName;
	string lastName;
	int bankRoll;
};
#endif //PLAYER_H

