#ifndef CARDPRINTER_H
#define CARDPRINTER_H

class Card;

class CardPrinter
{
public:
	static void Print(Card * card);
private:
	const static char * cardinalString[];
	const static char * suitString[];
};

#endif // CARDPRINTER_H
