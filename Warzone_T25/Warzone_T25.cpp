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
	cout << *map;
	GameEngine* engine = new GameEngine(map);
	Player* player1 = new Player(1,"Yasser",50);
	map->assignOccupantToTerritory(1, player1);
	Territory* territory = map->getTerritory(1);
	Territory* territory2 = map->getTerritory(2);
	territory->setNumArmies(20);
	player1->assignTerritoryToPlayer(territory);
	cout << *player1;
	//part_1::start();  
	//part_2::start();
	//part_3::start();
	//part_4::start();
	//part_5::start();


}

/*
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

