#ifndef CARDPRINTER_H
#define CARDPRINTER_H

#include <vector>

class Card;
class Deck;
class Seat;
class HandStrength;

class CardPrinter
{
public:
	static void Print(Card * card);
	static void PrintHandStrength(HandStrength * handStrength);
	static void PrintDeck(Deck * deck);
	static void PrintSeats(const std::vector<Seat*> &seats);
private:
	const static char * cardinalString[];
	const static char * suitString[];
	const static char * strengthString[];
};

#endif // CARDPRINTER_H
