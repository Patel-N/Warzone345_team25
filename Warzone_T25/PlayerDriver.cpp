#pragma once
#include <iostream>
#include "Player.h"
#include "TerritoryDUMMY.h"
#include "HandDUMMY.h"
#include "CardDUMMY.h"
#include <string>
#include "OrderDUMMY.h"
using namespace std;



void part_3::start() {
		
		cout << "**********************PLAYER PART**********************" << endl;

		//territory part--------------
		Player player1; // create new player
		TerritoryDUMMY*t1 = new TerritoryDUMMY; //creating 2 territories and assigning them to pointers
		t1->name = "Japan";
		TerritoryDUMMY* t2 = new TerritoryDUMMY;
		t2->name = "China";

		cout << "Player1 has territory:" << endl;
		player1.Territoryptr = { t1,t2 }; //adding territory pointers into the list of territory of the player		
		for (auto& elm : player1.Territoryptr) {//spitting out elements from the list of territories from player	
			cout << elm->name << endl;
		}

		//card part------------------
		HandDUMMY h1; // creat a hand object
		CardDUMMY*c1  = new CardDUMMY; //create 2 cards and have pointers associated with them
		c1->name = "diplomacy";
		CardDUMMY* c2 = new CardDUMMY;
		c2->name = "reinforcement";	
		h1.Cardptr = { c1,c2 };// inserting cards into hand1
		player1.Handptr = { &h1 };// player now owns hand1 with all its cards

		cout << "Player1 holds cards:" << endl;	
		for (auto& elm : player1.Handptr->Cardptr) {//spitting out elements from the list of cards from player	
			cout << elm->name << endl;
		}
		
		//to defend to defend method part ---------
		player1.Territoryptr = { t1 }; //ressting list of player
		cout << "Player1 is attacking:" << endl;
		for (auto& elm : player1.toDefend()) {//spitting out elements from the list of territories from player to defend
			cout << elm->name << endl;
		}
		//to defend to attack method part --------
		player1.Territoryptr = { t2 }; //ressting list of player
		cout << "Player1 is attacking:" << endl;
		for (auto& elm : player1.toAttack()) {//spitting out elements from the list of territories from player to attack
			cout << elm->name << endl;
		}
		

		//issueorder part -------------
		player1.issueOrder();
		player1.issueOrder();
		cout << "Player1 has orders:" << endl;
		for (auto& elm : player1.Orderptr) {//spitting out orders from the list of orders from player list of orders
			cout << elm->name << endl;
		}
		
		//copy const part -------
		cout << ""<< endl;
		Player player2(player1);
		cout << "player 2 has territories:" << endl;
		for (auto& elm : player2.Territoryptr) {//spitting out elements from the list of territories from player to defend
			cout << elm->name << endl;
		}
		cout << "Player2 holds cards:" << endl;
		for (auto& elm : player2.Handptr->Cardptr) {//spitting out elements from the list of cards from player	
			cout << elm->name << endl;
		}
		cout << "Player2 has orders:" << endl;
		for (auto& elm : player2.Orderptr) {//spitting out orders from the list of orders from player list of orders
			cout << elm->name << endl;
		}

		//stream insertion part--------	
		cout << "" << endl; //cout part
		cout << "stream insertion part: " << endl;
		cout << player1;
		cout << "please enter a territory: " << endl;
		cin >> player1; //cin part
		cout << "player1 has territory: " << endl;
		for (auto& elm : player1.Territoryptr) {//spitting out elements from the list of territories from player	
			cout << elm->name << endl;
		}

		//assignment operater overloading part--------
		cout << "" << endl;
		cout << "assignment operater overloading part:" << endl;
		Player player3 ;
		player3 = player1;	
		cout << "player 3 has territories:" << endl;
		for (auto& elm : player3.Territoryptr) {//spitting out elements from the list of territories from player to defend
			cout << elm->name << endl;
		}
		cout << "Player3 holds cards:" << endl;
		for (auto& elm : player3.Handptr->Cardptr) {//spitting out elements from the list of cards from player	
			cout << elm->name << endl;
		}
		cout << "Player3 has orders:" << endl;
		for (auto& elm : player3.Orderptr) {//spitting out orders from the list of orders from player list of orders
			cout << elm->name << endl;
		}
		
		cout <<"**********************END OF PLAYER PART**********************" << endl;
		
	}

