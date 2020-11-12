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
	//cout << *map;
	GameEngine* engine = new GameEngine(map);
	Player* player1 = new Player(1,"Yasser");
	Player* player2 = new Player(2, "Neil");
	engine->addPlayer(player1);
	engine->addPlayer(player2);
	//cout << *map;

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
	map->assignOccupantToTerritory(8, player1);
	Territory* territory8 = map->getTerritory(8);
	player1->assignTerritoryToPlayer(territory8);
	map->assignOccupantToTerritory(9, player1);
	Territory* territory9 = map->getTerritory(9);
	player1->assignTerritoryToPlayer(territory9);

	engine->reinforcementPhase();
	//cout << *player1;
	//part_1::start();  
	part_2::start();
	//part_3::start();
	//part_4::start();
	//part_5::start();

	cout << "testttt" << endl;
	Player* player3 = new Player(3, "p3");
	Player* player4 = new Player(4, "p4");

	Territory *ter3 = new Territory();
	ter3->setTerritoryName("ter3");
	Territory* ter4 = new Territory();
	ter4->setTerritoryName("ter4");
	Territory* ter5 = new Territory();
	ter5->setTerritoryName("ter5");
	Territory* ter6 = new Territory();
	ter6->setTerritoryName("ter6");

	player3->assignTerritoryToPlayer(ter3);
	player3->assignTerritoryToPlayer(ter4);
	player4->assignTerritoryToPlayer(ter5);
	player4->assignTerritoryToPlayer(ter6);

	cout << endl;
	cout << "printout:" << endl;
	cout << "from p3:"<< player3->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p3:" << player3->getPlayerTerritories()[1]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[1]->getName() << endl;
	*player3 = *player4;
	
	cout << "after op assignment, p3 now has p4" << endl;
	cout << "from p3:" << player3->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p3:" << player3->getPlayerTerritories()[1]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[1]->getName() << endl;
	cout << "after op changing name of ter3" << endl;
	player4->getPlayerTerritories()[0]->setTerritoryName("ter3 changed name");
	player4->getPlayerTerritories()[1]->setTerritoryName("ter3 changed name2");
	cout << "from p3:" << player3->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p3:" << player3->getPlayerTerritories()[1]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[0]->getName() << endl;
	cout << "from p4:" << player4->getPlayerTerritories()[1]->getName() << endl;

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