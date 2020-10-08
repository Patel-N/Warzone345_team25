#include <iostream>
#include "Cards.h"
#include <vector>


using namespace std;

int main()
{
	// Created the deck
	std::cout << "Creating deck.\n";
	Deck* cardDeck = new Deck();
	

	// Initializes deck with 25 cards and random number of each type.
	std::cout << "Adding cards to deck.\n";
	for (int i = 1; i <= 25; i++) {
		//cardDeck->addCardToDeck(new Card());
		Card* card = new Card();
		card->set_type(rand() %5 + 1);
		cardDeck->addCardToDeck(card);
		
	}

	std::cout << "25 cards were added to the deck.\n";

	//int numPlayers;
	//std::cout << "Enter number of players: \n";
	//std::cin >>numPlayers;

	// Creating hand objects based on number of players.
	std::cout << "Creating a hand for each player .\n";
	Hand* hand = new Hand();
	Hand* hand1 = new Hand();

	std::cout << "Adding cards to hand.\n";
	hand-> addCardToHand(cardDeck->draw());
	
	cout << "Playing cards.\n";
	//hand.play(hand.)
	





}
