#ifndef DECK_H
#define DECK_H

class Card;

#define DECKSIZE 52

class Deck 
{

public:
	
	Deck(Card* inCardInstance);
	~Deck();
	void Shuffle();
	Card* Pop();
	
private:
	Card* cards[52];
	Card* cardInstance;
	int nextCard;	

};
#endif //DECK_H

