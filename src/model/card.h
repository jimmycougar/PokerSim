#ifndef CARD_H
#define CARD_H

#define NUMSUITS 4
#define NUMCARDINALS 13

class Card
{

public:
	enum Cardinal  
	{       
		ACE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING
	};

	enum Suit
	{
		HEART,
		DIAMOND,
		SPADE,
		CLUB
	};

	Card();
	Card(Cardinal inCardinal, Suit inSuit);

	Cardinal GetCardinal();
	Suit GetSuit();
		
private:

	Cardinal cardinal;
	Suit suit;

};
#endif //CARD_H

