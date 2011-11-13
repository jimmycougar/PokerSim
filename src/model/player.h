#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using std::string;

class Player
{
	
public:

	Player(string inFirstName, string inLastName, int inBankRoll, int inStackSize);
	~Player();

	void PostBigBlind();
	void PostSmallBlind();
	void Fold();
	void Call();
	void Raise();
	int GetStackSize();
	string GetFirstName();
	string GetLastName();

private:

	string firstName;
	string lastName;
	int bankRoll;
	int stackSize;
};
#endif //PLAYER_H

