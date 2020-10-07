#include "Cards.h"
#include <string>
#include <iostream>

using namespace std; 

Card::Card() {

}

Card::Card(int typ, Deck* deck) {
	this->kind = typ;
	this->deck = deck;
}

Card::~Card() {

}

void Card::set_type(int new_kind) {

	switch (new_kind) {
	case 1: std::cout << "Bomb card set.\n";
	case 2: std::cout << "Reinforcement card set.\n";
	case 3: std::cout << "Blockade card set.\n";
	case 4: std::cout << "Airlift card set.\n";
	case 5: std::cout << "Diplomacy card set.\n";

	}
}

int Card::get_type() {
	return t;
}

Deck::Deck() {

}

Deck::~Deck() {

}

void Deck::addCardToDeck(Card* card) {

}

Card* Deck::draw()
{
	int randCard = rand() % 25 + 1;

	// Reference of randCard to card object
	Card* c = deck.at(randCard);
	return c;
}
Hand::Hand() {

}

Hand::~Hand() {

}
