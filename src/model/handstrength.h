#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H

#include "model/card.h"


class HandStrength
{
public:
	HandStrength(Card ** cards, int numCards);
	bool operator<(const HandStrength & other);
	bool operator==(const HandStrength & other);
private:
	enum HandType {
		NoPair,
		OnePair,
		TwoPair,
		ThreeOfAKind,
		Straight,
		Flush,
		FullHouse,
		FourOfAKind,
		StraightFlush };

	HandType handType;
	int handVal[5];
};

#endif // HANDSTRENGTH_H
