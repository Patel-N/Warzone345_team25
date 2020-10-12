#include <iostream>
#include "Cards.h"
#include <vector>


using namespace std;

void part_5::start()
{
	// Created the deck
	std::cout << "Creating deck: " << endl;
	Deck* cardDeck = new Deck();
	

	// Initializes deck with 25 cards and random number of each type.
	std::cout << "Adding cards to deck.\n" << endl;
	for (int i = 1; i <= 25; i++) {
		Card* card = new Card(rand() % 5 + 1);
		card->set_type(rand() %5 + 1);
		cardDeck->addCardToDeck(card);
		
		// Assignment operator
		if (i == 24) {
			Card* card3;
			card3 = card;

			// Insertion Stream Operator
			cout << "\nInsertion stream for card3 object: " << *card3 << endl;
			cout << "Assignment Operator: \ncard.type: " << card->get_type() << " Address: " << &card << endl;
			cout << "card3.type: " << card3->get_type() << " Address: " << &card3 << endl;
		}

		// Copy contructor
		if (i == 25) {
			Card* card2 = card;
			cout << "\nCopy Constructor: " << endl;
			cout << "card.type: " << card->get_type() << " Address: " << &card << endl;
			cout << "card2.type: " << card2->get_type() << " Address: " << &card2 << endl;

		}

		
	}


	std::cout << "\n25 cards were added to the deck.\n" << endl;

	//int numPlayers;
	//std::cout << "Enter number of players: \n";
	//std::cin >>numPlayers;

	// Creating hand objects based on number of players.
	std::cout << "Creating a hand for each player." << endl;
	Hand* hand = new Hand();
	Hand* hand1 = new Hand();

	std::cout << "Adding cards to hand.\n" << endl;
	hand-> addCardToHand(cardDeck->draw());
	
	cout << "\nPlaying cards." << endl;
	hand->play(hand->hand_getCard(), cardDeck);

	delete cardDeck;
	delete hand;
	delete hand1;
	





}
