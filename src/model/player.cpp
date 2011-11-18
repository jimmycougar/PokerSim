#include <string>

#include "player.h"

Player::Player(string inFirstName, string inLastName, int inBankRoll) : 
	firstName(inFirstName),
	lastName(inLastName),
	bankRoll(inBankRoll)
{
}

Player::~Player() 
{

}

int Player::PostBlind(int blindSize) 
{
	return blindSize;
}

int Player::GetPlayerAction(int betSize)
{
	return betSize;
}

void Player::notifyCard(Card * card)
{
	
}

void Player::notifyAction(int seatNum, int betSize)
{

}

string Player::GetFirstName()
{
	return firstName;
}

string Player::GetLastName()
{
	return lastName;
}
