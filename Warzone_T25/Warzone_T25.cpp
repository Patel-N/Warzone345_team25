// Warzone_T25.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include"Cards.h"
#include"Map.h"
#include "MapLoader.h"
#include"Player.h"
#include"GameEngine.h"
int main()
{
	MapLoader* loader = new MapLoader();
	Map* map;
	map = new Map(loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);
	Player* player1 = new Player(1,"Yasser");
	Player* player2 = new Player(2, "Neil");
	engine->addPlayer(player1);
	engine->addPlayer(player2);

	cout << "please" << endl << endl;
	Territory* t = map->getTerritory(1)->getAdjacentTerritories()[0];
	cout << t << endl << endl;

	//cont 1
	map->assignOccupantToTerritory(1, player1);
	Territory* territory = map->getTerritory(1);
	player1->assignTerritoryToPlayer(territory);
	map->assignOccupantToTerritory(2, player1);
	Territory* territory2 = map->getTerritory(2);
	player1->assignTerritoryToPlayer(territory2);
	map->assignOccupantToTerritory(3, player1);
	Territory* territory3 = map->getTerritory(3);
	player1->assignTerritoryToPlayer(territory3);
	map->assignOccupantToTerritory(4, player1);
	Territory* territory4 = map->getTerritory(4);
	player1->assignTerritoryToPlayer(territory4);
	map->assignOccupantToTerritory(5, player1);
	Territory* territory5 = map->getTerritory(5);
	player1->assignTerritoryToPlayer(territory5);
	
	//cont 2
	map->assignOccupantToTerritory(6, player1);
	Territory* territory6 = map->getTerritory(6);
	player1->assignTerritoryToPlayer(territory6);
	map->assignOccupantToTerritory(7, player1);
	Territory* territory7 = map->getTerritory(7);
	player1->assignTerritoryToPlayer(territory7);
	territory7->setNumArmies(13);
	map->assignOccupantToTerritory(8, player1);
	Territory* territory8 = map->getTerritory(8);
	player1->assignTerritoryToPlayer(territory8);
	map->assignOccupantToTerritory(9, player1);
	Territory* territory9 = map->getTerritory(9);
	player1->assignTerritoryToPlayer(territory9);
	territory9->setNumArmies(10);


	map->assignOccupantToTerritory(10, player2);
	Territory* territory10 = map->getTerritory(10);
	player2->assignTerritoryToPlayer(territory10);
	territory10->setNumArmies(5);

	map->assignOccupantToTerritory(11, player2);
	Territory* territory11 = map->getTerritory(11);
	player2->assignTerritoryToPlayer(territory11);
	territory11->setNumArmies(15);

	map->assignOccupantToTerritory(22, player2);
	Territory* territory22 = map->getTerritory(22);
	player2->assignTerritoryToPlayer(territory22);
	territory22->setNumArmies(30);

	map->assignOccupantToTerritory(23, player2);
	Territory* territory23 = map->getTerritory(23);
	player2->assignTerritoryToPlayer(territory23);
	territory23->setNumArmies(8);

	cout << "REINFORCEMENT PHASE:" << endl;
	engine->reinforcementPhase();
	cout << endl << endl;
	cout << "ISSUE ORDER PHASE:" << endl;
	engine->issueOrdersPhase();
	//cout << *player1;
	//part_1::start();  
	//part_2::start();
	//part_3::start();
	//part_4::start();
	//part_5::start();
}

/*
* 
* 
	Player:
		Go through everything with Martin
		Outputstream needs to be updated


	Order:
		Check abstract implementation and see how it would work for issuing Orders

	Map:
		Create method to assigning player* to a territory

	MapLoader:
		InputStream

	Cards:
		Make sure everything is good
*/