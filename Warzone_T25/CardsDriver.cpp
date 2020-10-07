#include <iostream>
#include "Cards.h"
#include <vector>


using namespace std;

int main()
{
	std::cout << "Creating deck.\n";
	Deck* cardDeck = new Deck();

	std::cout << "Adding cards to deck.\n";
	for (int i = 1; i <= 25; i++) {
		//deck->addCardToDeck(new Card());
		Card* card = new Card();
		card->set_type(rand() %5 + 1);
		cardDeck->addCardToDeck(card);
		
	}

	std::cout << "25 cards were added to the deck.\n";

	int numPlayers;
	std::cout << "Enter number of players: \n";
	std::cin >>numPlayers;

	std::cout << "Creating a hand for each player .\n";
	Hand* hand = new Hand();

	std::cout << "Adding cards to hand.\n";
	 cardDeck->draw();
	}






}
