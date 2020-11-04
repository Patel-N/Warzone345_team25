#include "Cards.h"
#include <string>
#include <iostream>

using namespace std; 

// CARD CLASS IMPLEMENTATIONS
// Constructors
Card::Card() {
	cout << "Card created with default constructor.\n" << endl;
}

Card::Card(int type) {
	this->type = type;
}

//Destructor
Card::~Card() {
	cout << "Card destroyed." << endl;
}

// Copy constructor to create deep copy when object is declared.
Card::Card(const Card& card) {
	cout << "Copy constructor called." << endl;
	type = card.type;
}

// Assignment Operator to create deep copy after object is declared.
Card &Card::operator= (const Card &card) {
	cout << "Assignemnt operator called." << endl;
	return *this;

}

// Insertion Stream Operator to get object value with ostream.
ostream& operator << (ostream& out, const Card& c)
{
	out << c.type << endl;
	return out;
}

// Sets type of card to an int and prints a the string corresponding to the int.
void Card::set_type(int new_kind) {

	switch (new_kind) {
	case 1: std::cout << "Bomb card set.\n";
	case 2: std::cout << "Reinforcement card set.\n";
	case 3: std::cout << "Blockade card set.\n";
	case 4: std::cout << "Airlift card set.\n";
	case 5: std::cout << "Diplomacy card set.\n";

	}
}

// Gets type of card.
int Card::get_type() {
	return type;
}

// This will be used to implement different card play methods.
void Card::play() {
	cout << "Special order created." << endl;
	cout << "Card played." << endl;
}

//DECK CLASS IMPLEMENTATIONS
//Constructor
Deck::Deck() {
	cout << "Deck created with default constructor.\n" << endl;;
}

// Destructor and memory leak prevention
Deck::~Deck() {
	for (int i = 0; i < deckVec.size(); i++) {
		delete deckVec[i];
	}

	deckVec.clear();
	cout << "Deck destroyed." << endl;
}
// Card pointer points to memory in vector.
void Deck::addCardToDeck(Card* card) {
	deckVec.push_back(card);
	
}

// Copy constructor to create a deep copy when object is declared.
Deck::Deck(const Deck& deck) {
	cout << "Copy constructor called." << endl;
	deckVec = deck.deckVec;
}

// Assignment Operator to create a deep copy after object is declared.
Deck& Deck::operator= (const Deck& deck) {
	cout << "Assignemnt operator called." << endl;
	return *this;

}

// Insertion Stream Operator to get object value with osstream.
ostream& operator << (ostream& out, const Deck& d)
{
	for (int i = 0; i < d.deckVec.size(); i++) {
		out << d.deckVec[i] << " " << endl;
	}
	return out;
}

// Card pointer points to memory in deck vector.
Card* Deck::draw()
{
	int randCard = rand() % deckVec.size();
	cout << "Deck size before draw: " << deckVec.size() << endl;
	Card* c = deckVec[randCard];
	cout << "ADDRESS OF CARD " << deckVec[randCard] << endl;
	deckVec.erase(deckVec.begin() + randCard);
	cout << "ADDRESS OF NEW CARD " << c << endl;
	//cout << c->get_type() << "\n";
	cout << "Deck size after draw: " << deckVec.size() << endl;

	return c;
}

// HAND CLASS IMPLEMENTATIONS
Hand::Hand() {

}

Hand::~Hand() {
	for (int i = 0; i < handCards.size(); i++) {
		delete handCards[i];
	}

	handCards.clear();
	cout << "Hand destroyed." << endl;
}

void Hand::addCardToHand(Card* card) {
	handCards.push_back(card);
}

Card* Hand::hand_getCard() {
	cout << "Getting first card: " << handCards[0]->get_type() << endl;
	return handCards[0];
}

void Hand::play(Card* playCard, Deck* deck) {
	for (int i = 0; i < handCards.size(); i++) {
		if (handCards[i]->get_type() == playCard->get_type()) {
			Card* ptr = handCards[i];
			handCards[i]->play();
			handCards.erase(handCards.begin() + i);
			deck->addCardToDeck(ptr);
			
		}


	}

}

// Copy constructor
Hand::Hand(const Hand& hand) {
	handCards = hand.handCards;
}

vector<Card*> Hand::getCardsInHand()
{
	return handCards;
}

// Assignment Operator
Hand& Hand::operator= (const Hand& hand) {
	cout << "Assignemnt operator called." << endl;
	return *this;

}

// Insertion Stream Operator
ostream& operator << (ostream& out, const Hand& h)
{
	for (int i = 0; i < h.handCards.size(); i++) {
		out << h.handCards[i] << " " << endl;
	}
	return out;
}