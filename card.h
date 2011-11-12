#ifndef CARD_H
#define CARD_H

class Card
{

	public:
		Card(NUMBER inNum, SUIT inSuit);

		NUMBER GetNumber();
		SUIT GetSuit();
		
		enum NUMBER 
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

		enum SUIT
		{
			HEART,
			DIAMOND,
			SPADE,
			CLUB
		};

	private:

		NUMBER num;
		SUIT suit;

};
#endif //CARD_H

