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
	type = card.type;
	return *this;

}

// Insertion Stream Operator to get object value with ostream.
ostream& operator << (ostream& out, const Card& c)
{
	switch (c.type) {
	case 1: out << "AIRLIFT CARD"<<endl;
		break;
	case 2: out << "BOMB CARD"<<endl;
		break;
	case 3: out << "BLOCKADE CARD"<<endl;
		break;
	case 4: out << "DIPLOMACY CARD"<<endl;
		break;
	case 5: out << "REINFORCEMENT CARD" << endl;
		break;
}
	return out;
}

// Sets type of card to an int and prints a the string corresponding to the int.
void Card::set_type(int new_kind) {

	switch (new_kind) {
	case 1: std::cout << "AIRLIFT card set.\n";
	case 2: std::cout << "BOMB card set.\n";
	case 3: std::cout << "BLOCKADE card set.\n";
	case 4: std::cout << "DIPLOMACY card set.\n";
	case 5: std::cout << "REINFORCEMENT card set.\n";

	}
}

// Gets type of card.
int Card::get_type() {
	return type;
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
	vector<Card*> cVec = deck.deckVec;
	for (int i = 0; i < deck.deckVec.size(); i++) {
		//Airlift
		if (cVec[i]->get_type() == 1) {
			Card* c = new Card(1);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 2) { //Bomb
			Card* c = new Card(2);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 3) { //Blockade
			Card* c = new Card(3);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 4) { //Negotiate
			Card* c = new Card(4);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 5) { //Reinforcement
			Card* c = new Card(5);
			this->addCardToDeck(c);
		}
	}
}

// Assignment Operator to create a deep copy after object is declared.
Deck& Deck::operator= (const Deck& deck) {
	cout << "Assignemnt operator called." << endl;
	if (this == &deck) {
		return *this;
	}
	vector<Card*> cVec = deck.deckVec;
	for (int i = 0; i < deck.deckVec.size(); i++) {
		//Airlift
		if (cVec[i]->get_type() == 1) {
			Card* c = new Card(1);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 2) { //Bomb
			Card* c = new Card(2);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 3) { //Blockade
			Card* c = new Card(3);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 4) { //Negotiate
			Card* c = new Card(4);
			this->addCardToDeck(c);
		}
		else if (cVec[i]->get_type() == 5) { //Reinforcement
			Card* c = new Card(5);
			this->addCardToDeck(c);
		}
	}
	return *this;
}

// Insertion Stream Operator to get object value with osstream.
ostream& operator << (ostream& out, const Deck& d)
{
	for (int i = 0; i < d.deckVec.size(); i++) {
		out << *d.deckVec[i] << " " << endl;
	}
	return out;
}

// Card pointer points to memory in deck vector.
Card* Deck::draw()
{
	int randCard = rand() % deckVec.size();
	cout << "Deck size before draw: " << deckVec.size() << endl;
	Card* c = deckVec[randCard];
	deckVec.erase(deckVec.begin() + randCard);
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

bool Hand::isCardInHand(int type) {
	for (int i = 0; i < handCards.size(); i++) {
		if (handCards[i]->get_type() == type) {
			return true;
		}
	}
	return false;
}

void Hand::play(int type, Deck* deck) {
	for (int i = 0; i < handCards.size(); i++) {
		if (handCards[i]->get_type() == type) {
			Card* ptr = handCards[i];
			handCards.erase(handCards.begin() + i);
			deck->addCardToDeck(ptr);
		}
	}
}
// Copy constructor
Hand::Hand(const Hand& hand) {
	if (this != &hand) {
		*this = hand;
	}
}

vector<Card*> Hand::getCardsInHand()
{
	return handCards;
}

// Assignment Operator
Hand& Hand::operator= (const Hand& ogHand) {
	cout << "Assignemnt operator called." << endl;
	if (ogHand.handCards.size() > 0) {
		vector<Card*>ogHandVec = ogHand.handCards;
		for (int i = 0; i < ogHandVec.size(); i++) {
			Card* card = new Card(*ogHandVec[i]);
			this->addCardToHand(card);
		}
	}
	return *this;
}

// Insertion Stream Operator
ostream& operator << (ostream& out, const Hand& h)
{
	for (int i = 0; i < h.handCards.size(); i++) {
		out << *h.handCards[i] << " " << endl;
	}
	return out;
}