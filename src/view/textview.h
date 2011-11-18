#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include "observer.h"

class TextView : public Observer
{
	virtual void notifyCard(Card * card);
	virtual void notifyAction(int seatNum, int bet);
	virtual void notifyHandShow(int seatNum, Card * card1, Card * card2, HandStrength * hand);
	virtual void notifyWinner(int seatNum, HandStrength * hand, int potSize);
};


#endif // TEXTVIEW_H
