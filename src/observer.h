#ifndef OBSERVER_H
#define OBSERVER_H

class Card;
class HandStrength;

class Observer
{
public:
	virtual void notifyBlinds(int sbSeat, int smallBlind, int bbSeat, int bigBlind){}
	virtual void notifyCard(Card * card){}
	virtual void notifyAction(int seatNum, int oldBet, int newBet, int betToCall){}
	virtual void notifyHandShow(int seatNum, Card * card1, Card * card2, HandStrength * hand){}
	virtual void notifyWinner(int seatNum, HandStrength * hand, int potSize){}
};

#endif // OBSERVER_H
