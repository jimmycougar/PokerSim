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

void Player::PostBigBlind() 
{

}

void Player::PostSmallBlind()
{

}

void Player::Fold() 
{

}

void Player::Call() 
{

}

void Player::Raise()
{

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
