#include <list>
#include <exception>

#include "model/handstrength.h"
#include "model/card.h"

HandStrength::HandStrength(Card ** cards, int numCards) :
	handType(NoPair)
{
	// hand cannot be evaluated
	if (numCards < 5)
		return;

	for(int i=0; i<5; ++i)
		handVal[i] = 0;

	bool flush = false;
	int flushSuit;
	bool straight = false;
	int straightHigh;

	std::list<int> fourOfKindSet, threeOfKindSet, twoOfKindSet, oneOfKindSet;

	int cardinal[NUMCARDINALS] = {0};
	std::list<int> suit[NUMSUITS];
	
	// count cardinals and sutis
	for(int i=0; i<numCards; ++i)
	{
		int thisCardinal = cards[i]->GetCardinal();
		++cardinal[thisCardinal];
		suit[cards[i]->GetSuit()].push_back(thisCardinal);
	}

	// check for flush and save its suit
	for(int i=0; i<NUMSUITS; ++i)
	{
		if(suit[i].size() >= 5)
		{
			flush = true;
			flushSuit = i;
			break;
		}
	}

	// check for straights and pairs
	int consec = 0;
	if(cardinal[Card::ACE])
		consec = 1;
	for(int i=0; i<NUMCARDINALS; ++i)
	{
		if(cardinal[i] == 0)
		{
			consec = 0;
			continue;
		}

		++consec;

		if(consec >= 5)
		{
			straight = true;
			straightHigh = i;
		}

		switch(cardinal[i])
		{
		case 4:
			fourOfKindSet.push_front(i);
			break;
		case 3:
			threeOfKindSet.push_front(i);
			break;
		case 2:
			twoOfKindSet.push_front(i);
			break;
		case 1:
			oneOfKindSet.push_front(i);
			break;
		case 0:
			break;
		default:
			// error case
			break;
		}
	}

	// check for straight flush
	if(straight && flush)
	{
		bool straightFlush = false;
		int straightFlushHigh;
		bool wheelEligible = false;
		bool aceForWheel = false;
		int last = -2;
		consec = 0;
		// copy the list so we can use it later despite popping
		std::list<int> suitedList = suit[flushSuit];
		while(!suitedList.empty())
		{
			int val = suitedList.front();
			suitedList.pop_front();
			if(val == last+1)
				++consec;
			else
				consec = 1;

			last = val;

			// wheel checking flags
			if(val == 5 && consec == 4)
				wheelEligible = true;
			if(val == Card::ACE)
				aceForWheel = true;

			if(consec >= 5)
			{
				straightFlush = true;
				straightFlushHigh = val;
			}
		}

		// check for wheel
		if(wheelEligible && aceForWheel && !straightFlush)
		{
			straightFlush = true;
			straightFlushHigh = 5;
		}

		if(straightFlush)
		{
			handType = StraightFlush;
			handVal[0] = straightFlushHigh;
			return;
		}
	}

	// check for 4 of a kind
	if(!fourOfKindSet.empty())
	{
		handType = FourOfAKind;
		handVal[0] = fourOfKindSet.front();
		
		for(int i=Card::ACE; i >= 0; --i)
		{
			if(i != handVal[0] && cardinal[i])
			{
				handVal[1] = cardinal[i];
				break;
			}
		}
		return;
	}

	// check for full house
	if((!threeOfKindSet.empty() && !twoOfKindSet.empty()) || threeOfKindSet.size() > 1)
	{
		handType = FullHouse;
		handVal[0] = threeOfKindSet.front();
		threeOfKindSet.pop_front();

		if(!threeOfKindSet.empty())
			handVal[1] = threeOfKindSet.front();

		if(!twoOfKindSet.empty())
			if(twoOfKindSet.front() > handVal[1])
				handVal[1] = twoOfKindSet.front();

		return;
	}

	// check for flush
	if(flush)
	{
		handType = Flush;
		for(int i=0; i<5; ++i)
		{
			handVal[i] = suit[flushSuit].back();
			suit[flushSuit].pop_back();
		}
		return;
	}

	// check for straight
	if(straight)
	{
		handType = Straight;
		handVal[0] = straightHigh;
		return;
	}

	// check for three of a kind
	if(!threeOfKindSet.empty())
	{
		handType = ThreeOfAKind;
		handVal[0] = threeOfKindSet.front();
		threeOfKindSet.pop_front();

		// get next two high card values - they could be in any of the sets
		if(!threeOfKindSet.empty())
			handVal[1] = threeOfKindSet.front();

		if(!twoOfKindSet.empty() && twoOfKindSet.front() > handVal[1])
		{
			handVal[1] = twoOfKindSet.front();
			twoOfKindSet.pop_front();
		}
		
		if(!twoOfKindSet.empty() && twoOfKindSet.front() > handVal[2])
			handVal[2] = twoOfKindSet.front();

		if(!oneOfKindSet.empty() && oneOfKindSet.front() > handVal[1])
		{
			handVal[1] = oneOfKindSet.front();
			oneOfKindSet.pop_front();
		}

		if(!oneOfKindSet.empty() && oneOfKindSet.front() > handVal[2])
			handVal[2] = oneOfKindSet.front();

		return;
	}

	// check for two pair
	if(twoOfKindSet.size() > 1)
	{
		handType = TwoPair;
		handVal[0] = twoOfKindSet.front();
		twoOfKindSet.pop_front();
		handVal[1] = twoOfKindSet.front();
		twoOfKindSet.pop_front();

		// get one high card value
		if(!twoOfKindSet.empty())
			handVal[2] = twoOfKindSet.front();

		if(oneOfKindSet.front() > handVal[2])
			handVal[2] = oneOfKindSet.front();

		return;
	}

	// check for one pair
	if(!twoOfKindSet.empty())
	{
		handType = OnePair;
		handVal[0] = twoOfKindSet.front();

		// set handVal for high cards
		for(int i=1; i<4; ++i)
		{
			handVal[i] = oneOfKindSet.front();
			oneOfKindSet.pop_front();
		}

		return;
	}

	// no pair
	handType = NoPair;
	for(int i=0; i<5; ++i)
	{
		handVal[i] = oneOfKindSet.front();
		oneOfKindSet.pop_front();
	}

}

bool HandStrength::operator<(const HandStrength & other)
{
	if(handType < other.handType)
		return true;
	else if(handType > other.handType)
		return false;

	for(int i=0; i<5; ++i)
	{
		if(handVal[i] < other.handVal[i])
			return true;
		else if(handVal[i] > other.handVal[i])
			return false;
	}

	return false;
}

bool HandStrength::operator==(const HandStrength & other)
{
	return handType == other.handType
		&& handVal[0] == other.handVal[0]
		&& handVal[1] == other.handVal[1]
		&& handVal[2] == other.handVal[2]
		&& handVal[3] == other.handVal[3]
		&& handVal[4] == other.handVal[4];
}

