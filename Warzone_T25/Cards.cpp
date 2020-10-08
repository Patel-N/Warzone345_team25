#include "Cards.h"
#include <string>
#include <iostream>

using namespace std; 

// CARD CLASS IMPLEMENTATIONS
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

void Card::setDeck(Deck* newDeck)
{
	if (deck == NULL)
	{
		deck = newDeck;
	}

}

void Card::play() {
	cout << "Card played." << endl;
}

//DECK CLASS IMPLEMENTATIONS
Deck::Deck() {
	cout << "Deck created in default constructor.\n";
	cout << this;

}

Deck::~Deck() {

}

void Deck::addCardToDeck(Card* card) {
	cout << "Adding card to deck" << endl;
	deck.push_back(card);
	
}


Card* Deck::draw()
{
	int randCard = rand() % deck.size();
	cout << "Deck size: " << deck.size() << endl;
	Card* c = deck[randCard];
	cout << "ADDRESS OF CARD " << deck[randCard] << endl;
	deck.erase(deck.begin() + randCard);
	cout << "ADDRESS OF NEW CARD " << c << endl;
	cout << c->get_type() << "\n";
	cout << deck.size() << "SIZE\n";

	return c;
}

// HAND CLASS IMPLEMENTATIONS
Hand::Hand() {

}

Hand::~Hand() {

}

void Hand::addCardToHand(Card* card) {
	handCards.push_back(card);
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
