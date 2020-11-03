#pragma once
#include <iostream>
#include <list>

#include "Cards.h"
#include "Orders.h"
using namespace std;
class Territory;
class Player
{
public:
	list<Territory*> Territoryptr; //BUG** TO DO
	Hand* Handptr;
	list<Order*> Orderptr;
public:
	//void issueOrder() ;
	//Player();
	//Player(const Player& input);
	//friend ostream& operator << (ostream& output, Player& obj);

	//friend istream& operator >> (istream& input, Player& obj);


	//list<Territory*> toDefend(); // returns list of territory pointers to defend



	//list<Territory*> toAttack();// returns list of territory pointers to defend


	//assignment operator overload
	//Player& operator = (const Player& input);



};
namespace part_3 {

	void start();

}
