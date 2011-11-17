#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H

#include <list>
#include "model/card.h"

class HandStrength
{
public:
	HandStrength(std::list<Card*> cards);
	bool operator<(const HandStrength & other) const;
	bool operator==(const HandStrength & other) const;

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

	std::list<int> handVal;
};

#endif // HANDSTRENGTH_H
