#include <iostream>

#include "textview.h"
#include "cardprinter.h"

using std::cout;

void TextView::notifyCard(Card * card)
{
	cout << "Dealer deals: ";
	CardPrinter::Print(card);
	cout << std::endl;
}

void TextView::notifyBlinds(int sbSeat, int smallBlind, int bbSeat, int bigBlind)
{
	cout << "Seat " << sbSeat << " posts " << smallBlind << " (Small Blind)\n";
	cout << "Seat " << bbSeat << " posts " << bigBlind << " (Big Blind)\n";
}

void TextView::notifyAction(int seatNum, int oldBet, int newBet, int betToCall)
{
	cout << "Seat " << seatNum;
	if(newBet < betToCall)
		cout << " folds";
	else if(betToCall == newBet && newBet == oldBet)
		cout << " checks";
	else if(betToCall == newBet)
		cout << " calls " << betToCall;
	else if(betToCall == 0)
		cout << " bets " << newBet;
	else if(newBet > betToCall)
		cout << " raises to " << newBet;
	else
		cout << "...something strange happened";

	cout << ".\n";
}

void TextView::notifyHandShow(int seatNum, Card * card1, Card * card2, HandStrength * hand)
{
	cout << "Seat " << seatNum << " shows ";
	CardPrinter::Print(card1);
	cout << " and ";
	CardPrinter::Print(card2);
	cout << ": ";
	CardPrinter::PrintHandStrength(hand);
}

void TextView::notifyWinner(int seatNum, HandStrength * hand, int potSize)
{
	cout << "Seat " << seatNum << " wins " << potSize << " with: ";
	CardPrinter::PrintHandStrength(hand);
}

