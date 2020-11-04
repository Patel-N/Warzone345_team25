#pragma once
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include <string>
#include "Orders.h"
using namespace std;



void part_3::start() {
	/*
		cout << "**********************PLAYER PART**********************" << endl;

		//territory part--------------
		Player player1; // create new player
		Territory*t1 = new Territory; //creating 2 territories and assigning them to pointers
		t1->name = "Japan";
		Territory* t2 = new Territory;
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
		*/
	//cout << "test" << endl;
	Player* p = new Player();
	Map* map = new Map("Created map");
	map->addContinent(1, "Skandinavien", 4);
	map->addContinent(2, "Westeuropa", 5);
	map->addContinent(3, "Mittelmeer", 3);
	map->addContinent(4, "Mitteleuropa", 4);
	/*map.addContinent(5, "Balkan", 3);
	map.addContinent(6, "Kleinasien", 3);
	map.addContinent(7, "Russland", 7);*/
	map->addTerritory(1, "Reykjavik", 1);
	map->addTerritory(2, "Ostisland", 1);
	map->addTerritory(3, "Glasgow", 2);
	map->addTerritory(4, "Glasgow", 2);
	map->addTerritory(5, "Nordirland", 2);
	map->addTerritory(6, "Dublin", 2);
	map->addTerritory(7, "Suedirland", 2);
	//map->addTerritory(7, "Suedirland", 3);
	//map->addTerritory(7, "Suedirland", 2);
	map->addTerritory(8, "Leeds", 2);
	map->addTerritory(9, "wales", 2);
	map->addTerritory(10, "England", 2);
	map->addTerritory(11, "London", 2);
	map->addTerritory(12, "Lisabon", 3);
	map->addTerritory(13, "Porto", 3);
	map->addTerritory(14, "Baskenl", 3);
	map->addTerritory(15, "Barcelona ", 4);
	map->addTerritory(16, "Madrid", 4);
	map->addTerritory(17, "Ballearen", 4);

	//std::cout << map;
	std::vector<int> border = { 1 };
	map->addBorder(border);
	border = { 2 };
	map->addBorder(border);
	border = { 3,7 };
	map->addBorder(border);
	border = { 4,3 };
	map->addBorder(border);
	border = { 5,6 };
	map->addBorder(border);
	border = { 6 };
	map->addBorder(border);
	border = { 7,2 };
	map->addBorder(border);
	border = { 8,4,9 };
	map->addBorder(border);
	border = { 9,5,13,10 };
	map->addBorder(border);
	border = { 10,6,11 };
	map->addBorder(border);
	border = { 12,13 };
	map->addBorder(border);
	border = { 13,14 };
	map->addBorder(border);
	border = { 14,9,10,11 };
	map->addBorder(border);
	border = { 15,7,17 };
	map->addBorder(border);
	border = { 16,8,13,15,17 };
	map->addBorder(border);

	p->assignTerritoryToPlayer(map->getContinents()[0]->getContinentTerritoryList()[0]);
	p->assignTerritoryToPlayer(map->getContinents()[0]->getContinentTerritoryList()[1]);

	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		cout << *(p->getPlayerTerritories()[i]);
	}

	/*
		Player:
			Go through everything with Martin


		Order:
			Check abstract implementation and see how it would work for issuing Orders
	
		Map:
			Create method to assigning player* to a territory

		MapLoader:
			InputStream

		Cards:
			Make sure everything is good
	*/
}

