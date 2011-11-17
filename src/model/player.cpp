#include <string>

#include "player.h"

Player::Player(string inFirstName, string inLastName, int inBankRoll, int inStackSize) : 
	firstName(inFirstName),
	lastName(inLastName),
	bankRoll(inBankRoll),
	stackSize(inStackSize)

{
}

Player::~Player() 
{

}

int Player::PostBigBlind() 
{
	return 2;
}

int Player::PostSmallBlind()
{
	return 1;
}

int Player::GetPlayerAction(int betSize)
{
	return 0;
}

int Player::GetStackSize()
{
	return stackSize;
}

string Player::GetFirstName()
{
	return firstName;
}

string Player::GetLastName()
{
	return lastName;
}
