#ifndef CARDPRINTER_H
#define CARDPRINTER_H

class Card;
class Deck;

class CardPrinter
{
public:
	static void Print(Card * card);
	static void PrintDeck(Deck * deck);
private:
	const static char * cardinalString[];
	const static char * suitString[];
};

#endif // CARDPRINTER_H
