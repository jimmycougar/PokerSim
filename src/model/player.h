#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player
{
	
public:

	Player(string inFirstName, string inLastName, int inBankRoll);
	~Player();

	int PostBlind(int blindSize);
	string GetFirstName();
	string GetLastName();
	int GetPlayerAction(int betSize);
	void NotifyPlayerAction(int seatNum, int betSize);

private:

	string firstName;
	string lastName;
	int bankRoll;
};
#endif //PLAYER_H

