#pragma once
#include <iostream>
#include <list>
#include "Territory.h"
#include "Hand.h"
#include "Order.h"
using namespace std;

class Player
{
public:
	list<Territory*> Territoryptr;
	Hand* Handptr;
	list<Order*> Orderptr;
public:
	void issueOrder() { 
		Order* neworder = new Order(); // creating new order and pointer
		list<Order*> temp = { neworder }; //temporary place pointer into a list
		Orderptr.merge(temp);// merg pointer into list of pointer

	};

	friend ostream& operator << (ostream& output, Player& obj) {
		Territory* ter = obj.Territoryptr.front();
		string tername = ter->name;
		output << "player has territory: " << tername << endl;
		return output;
	}

	friend istream& operator >> (istream& input, Player& obj) {
		Territory* tempter = new Territory;
		string mystring;
		getline(cin, mystring);
		tempter->name = mystring;
		obj.Territoryptr.push_back(tempter);
		return input;


	}
};

