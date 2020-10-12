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


	list<Territory*> toDefend() {// returns list of territory pointers to defend
		return  { Territoryptr };
	};

	list<Territory*> toAttack() {// returns list of territory pointers to defend
		return  { Territoryptr };
	};

	//assignment operator overload
	Player& operator = (const Player& input) {
		// duplicating territory
		for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory          
			Territory* temptr = new Territory; // creating new territory pointer and territory
			temptr->name = elm->name; // giving territory same name from input player
			list<Territory*> tempList = { temptr }; //temporary place pointer into a list
			Territoryptr.merge(tempList);// merg pointer into list of pointer
		}
		//duplicating hand
		Handptr = new Hand; // creating new hand for new player
		for (auto& elm : input.Handptr->Cardptr) {// for every card in input player cards       
			Card* tempcard = new Card; // creating new card pointer and card
			tempcard->name = elm->name; // giving card same name from input player
			list<Card*> tempList = { tempcard }; //temporary place pointer into a list
			Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
		}
		//duplicating order
		for (auto& elm : input.Orderptr) {// for every order in input player order list       
			Order* temporder = new Order; // creating new order pointer and order
			temporder->name = elm->name; // giving order same name from input player
			list<Order*> tempList = { temporder }; //temporary place pointer into a list
			Orderptr.merge(tempList);// merg pointer into list of pointer
		}
		
		
		
		return *this;
		
	}

};

