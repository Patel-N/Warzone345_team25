#pragma once
#include <string>
#include <vector>
#include <unordered_set>

#include <ctime>
#include <iostream>

enum type {bomb = 1, reinforcement = 2, blockade = 3, airlift = 4, diplomacy = 5};

// Forward declaration in order to avoid a circular dependency of pointers between classes.
class Card;
class Deck;
class Hand;

class Card {

public:
	Card();
	~Card();
	Card(int kind ,Deck* deck);

	void set_type(int new_kind);
	int get_type();

	void setDeck(Deck* deck);
	void play();

private:
	Deck* deck;
	type t;
	int kind;


};

class Deck {

public:
	Deck();
	~Deck();
	void addCardToDeck(Card* card);
	Card* draw();

private:
	std::vector<Card*> deck;

};

class Hand {

public:
	Hand();
	~Hand();

	void addCardToHand(Card* card);
	void play(Card* playCard, Deck* deck);


private:
	std::vector<Card*> handCards;
	//vector<Card*> playCards;

};