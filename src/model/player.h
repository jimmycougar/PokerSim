#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player
{
	
public:

	Player(string inFirstName, string inLastName, int inBankRoll, int inStackSize);
	~Player();

	int PostBigBlind();
	int PostSmallBlind();
	int GetStackSize();
	string GetFirstName();
	string GetLastName();
	int GetPlayerAction(int betSize);

private:

	string firstName;
	string lastName;
	int bankRoll;
	int stackSize;
};
#endif //PLAYER_H

