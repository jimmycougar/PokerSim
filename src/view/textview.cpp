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

void TextView::notifyAction(int seatNum, int bet)
{
	cout << "Seat " << seatNum << " bets: " << bet << std::endl;
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

