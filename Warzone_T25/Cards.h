#pragma once
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

enum type {bomb = 1, airlift = 2, reinforcement = 3};

// Forward declaration in order to avoid a circular dependency of pointers between classes.
class Card;
class Deck;
class Hand;

class Card {

private:
	Deck* deck;
	type t;
	int kind;
public:
	Card();
	Card(int kind ,Deck* deck);
	~Card();
	void set_type(int new_kind);
	int get_type();
};

class Deck {
public:
	Deck();
	~Deck();
	void addCardToDeck(Card* card);
	Card* draw();

private:
	vector<Card*> deck;


};

class Hand {
public:
	Hand();
	~Hand();
	

};

//class Bomb : public Card {
//	int type;
//
//public:
//	void set_type(int new_type);
//	int get_type();
//};
//
//class Reinforcement : public Card {
//	int type;
//
//public:
//	void set_type(int new_type);
//	int get_type();
//};
//
//class Blockade : public Card {
//	int type;
//
//public:
//	void set_type(int new_type);
//	int get_type();
//};
//
//class Airlift : public Card {
//	int type;
//
//public:
//	void set_type(int new_type);
//	int get_type();
//};
//
//class Diplomacy : public Card {
//	int type;
//
//public:
//	void set_type(int new_type);
//	int get_type();
//};