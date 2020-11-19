#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <iostream>
using namespace std;
/*CARD TYPES:
1: AIRLIFT
2: BOMB
3: BLOCKADE
4: DIPLOMACY
5:REINFORCEMENT
*/

// Forward declaration in order to avoid a circular dependency of pointers between classes.
class Card;
class Deck;
class Hand;

class Card {

public:
	// Constructors
	Card();
	~Card();
	Card(int type);

	// Copy Constructor
	Card(const Card& card);


	// Assignment Operator
	Card& operator = (const Card& card);

	// Insertion Stream Operator
	friend ostream& operator << (ostream& out, const Card& c);

	void set_type(int new_kind);
	int get_type();

	void setDeck(Deck* deck);

	// Included in order to implement actual play method of Cards later on.
	void play();

private:
	Deck* deck;
	int type;
};

class Deck {

public:
	// Constructors
	Deck();
	~Deck();

	void addCardToDeck(Card* card);
	
	//Getters INLINE
	inline int getDeckSize() { return deckVec.size(); }

	// Removes card from deck and adds it to hand.
	Card* draw();

	// Copy Constructor
	Deck(const Deck& deck);

	// Assignment Operator
	Deck& operator = (const Deck& deck);

	// Insertion Stream Operator
	friend ostream& operator << (ostream& out, const Deck& d);

private:
	std::vector<Card*> deckVec;

};

class Hand {

public:
	// Contructors

	Hand();
	~Hand();

	// Copy Constructor
	Hand(const Hand& hand);

	//Getters
	vector<Card*> getCardsInHand();

	// Assignment Operator
	Hand& operator = (const Hand& hand);

	// Insertion Stream Operator
	friend ostream& operator << (ostream& out, const Hand& h);

	void addCardToHand(Card* card);
	bool isCardInHand(int);
	// Gets card from hand, plays it and returns it to deck.
	void play(int, Deck*);
	void removeCardFromHand(int id);
	Card* hand_getCard();



private:
	std::vector<Card*> handCards;
};

namespace part5 {
	void start();
}