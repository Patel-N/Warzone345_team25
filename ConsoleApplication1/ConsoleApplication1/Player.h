#pragma once
#include <iostream>
#include <list>
#include "TerritoryDUMMY.h"
#include "HandDUMMY.h"
#include "OrderDUMMY.h"
using namespace std;

class Player
{
public:
	list<TerritoryDUMMY*> Territoryptr;
	HandDUMMY* Handptr;
	list<OrderDUMMY*> Orderptr;
public:
	void issueOrder() ;
	Player();
	Player(const Player& input);
	friend ostream& operator << (ostream& output, Player& obj);

	friend istream& operator >> (istream& input, Player& obj);


	list<TerritoryDUMMY*> toDefend(); // returns list of territory pointers to defend
		
	

	list<TerritoryDUMMY*> toAttack();// returns list of territory pointers to defend


	//assignment operator overload
	Player& operator = (const Player& input);
		
	

};
namespace part3 {

	void start();
	
}
