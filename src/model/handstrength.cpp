#include <list>
#include <exception>

#include "model/handstrength.h"
#include "model/card.h"

HandStrength::HandStrength(std::list<Card*> cards)
{
	// hand cannot be evaluated
	if (cards.size() < 5)
		return;

	bool flush = false;
	int flushSuit;
	bool straight = false;
	int straightHigh;

	std::list<int> fourOfKindSet, threeOfKindSet, twoOfKindSet, oneOfKindSet;

	int cardinal[NUMCARDINALS] = {0};
	std::list<int> suit[NUMSUITS];
	
	// count cardinals and suits
	for(std::list<Card*>::iterator i=cards.begin(); i != cards.end(); ++i)
	{
		int thisCardinal = (*i)->GetCardinal();
		++cardinal[thisCardinal];
		suit[(*i)->GetSuit()].push_back(thisCardinal);
	}

	// check for flush and save its suit
	for(int i=0; i<NUMSUITS; ++i)
	{
		if(suit[i].size() >= 5)
		{
			flush = true;
			flushSuit = i;
			suit[flushSuit].sort();
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
			handVal.push_back(StraightFlush);
			handVal.push_back(straightFlushHigh);
			return;
		}
	}

	// check for 4 of a kind
	if(!fourOfKindSet.empty())
	{
		handVal.push_back(FourOfAKind);
		handVal.push_back(fourOfKindSet.front());
		
		for(int i=Card::ACE; i >= 0; --i)
		{
			if(i != handVal.front() && cardinal[i])
			{
				handVal.push_back(cardinal[i]);
				break;
			}
		}
		return;
	}

	// check for full house
	if((!threeOfKindSet.empty() && !twoOfKindSet.empty()) || threeOfKindSet.size() > 1)
	{
		handVal.push_back(FullHouse);
		handVal.push_back(threeOfKindSet.front());
		threeOfKindSet.pop_front();

		handVal.push_back(-1);

		if(!threeOfKindSet.empty())
		{
			handVal.pop_back();
			handVal.push_back(threeOfKindSet.front());
		}

		if(!twoOfKindSet.empty())
			if(twoOfKindSet.front() > handVal.back())
			{
				handVal.pop_back();
				handVal.push_back(twoOfKindSet.front());
			}

		return;
	}

	// check for flush
	if(flush)
	{
		handVal.push_back(Flush);
		for(int i=0; i<5; ++i)
		{
			handVal.push_back(suit[flushSuit].back());
			suit[flushSuit].pop_back();
		}
		return;
	}

	// check for straight
	if(straight)
	{
		handVal.push_back(Straight);
		handVal.push_back(straightHigh);
		return;
	}

	// check for three of a kind
	if(!threeOfKindSet.empty())
	{
		handVal.push_back(ThreeOfAKind);
		handVal.push_back(threeOfKindSet.front());
		threeOfKindSet.pop_front();

		// get next two high card values - they can only be in oneOfKind, or else this would be a full house
		if(!oneOfKindSet.empty()) 
		{
			handVal.push_back(oneOfKindSet.front());
			oneOfKindSet.pop_front();
		}

		if(!oneOfKindSet.empty())
			handVal.push_back(oneOfKindSet.front());

		return;
	}

	// check for two pair
	if(twoOfKindSet.size() > 1)
	{
		handVal.push_back(TwoPair);
		handVal.push_back(twoOfKindSet.front());
		twoOfKindSet.pop_front();
		handVal.push_back(twoOfKindSet.front());
		twoOfKindSet.pop_front();

		handVal.push_back(-1);

		// get one high card value
		if(!twoOfKindSet.empty())
		{
			handVal.pop_back();
			handVal.push_back(twoOfKindSet.front());
		}

		if(oneOfKindSet.front() > handVal.back())
		{
			handVal.pop_back();
			handVal.push_back(oneOfKindSet.front());
		}

		return;
	}

	// check for one pair
	if(!twoOfKindSet.empty())
	{
		handVal.push_back(OnePair);
		handVal.push_back(twoOfKindSet.front());

		// set handVal for high cards
		for(int i=1; i<4; ++i)
		{
			handVal.push_back(oneOfKindSet.front());
			oneOfKindSet.pop_front();
		}

		return;
	}

	// no pair
	handVal.push_back(NoPair);
	for(int i=0; i<5; ++i)
	{
		handVal.push_back(oneOfKindSet.front());
		oneOfKindSet.pop_front();
	}

}

bool HandStrength::operator<(const HandStrength & other) const
{
	std::list<int>::const_iterator myIter, otherIter;
	myIter = handVal.begin();
	otherIter = other.handVal.begin();

	while(myIter != handVal.end() && otherIter != other.handVal.end())
	{
		if(*myIter < *otherIter)
			return true;
		else if(*myIter > *otherIter)
			return false;

		++myIter;
		++otherIter;
	}
	// hands are equal
	return false;
}

bool HandStrength::operator==(const HandStrength & other) const
{
	// if neither hand is less than the other, they are equal
	return !(operator<(other) ||
			other.operator<(*this));
}

