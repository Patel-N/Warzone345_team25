// Warzone_T25.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include"Cards.h"
#include"Map.h"
#include "MapLoader.h"
#include"Player.h"
#include"GameEngine.h"
#include "Part2Driver.h"
#include"GameObservers.h"
#include "Part1GameEngine.h"

int main()
{


	//creating game engine, creating map, loading canada map
	MapLoader* loader = new MapLoader();
	Map* map = (loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);

	//part_1::start();  
	//part_2::start(); 
	//part_3::start();
	//part_4::start();
	//part_5::start();



	Deck* deck = new Deck();
	Player::common_deck = deck;
	for (int i = 1; i <= 25; i++) {
		Card* card = new Card(rand() % 5 + 1);
		card->set_type(rand() % 5 + 1);
		deck->addCardToDeck(card);
	}

	Player* player1 = new Player(1, "Neil", 1, 1);
	Player* player2 = new Player(2, "Martin", 2, 1);
	Player* player3 = new Player(3, "Paurush", 3, 1);
	Player* player4 = new Player(4, "Vishal", 4, 1);

	Hand* hand_p1 = new Hand();
	Hand* hand_p2 = new Hand();
	Hand* hand_p3 = new Hand();
	Hand* hand_p4 = new Hand();
	//setting player's hand
	player1->setPlayerHand(hand_p1);
	player2->setPlayerHand(hand_p2);
	player3->setPlayerHand(hand_p3);
	player4->setPlayerHand(hand_p4);

	engine->addPlayer(player1);
	engine->addPlayer(player2);
	engine->addPlayer(player3);
	engine->addPlayer(player4);

	engine->getGameMap()->assignOccupantToTerritory(1, player1);
	engine->getGameMap()->assignOccupantToTerritory(2, player1);
	engine->getGameMap()->assignOccupantToTerritory(3, player1);
	engine->getGameMap()->assignOccupantToTerritory(4, player1);
	engine->getGameMap()->assignOccupantToTerritory(5, player1);
	engine->getGameMap()->assignOccupantToTerritory(6, player2);
	engine->getGameMap()->assignOccupantToTerritory(7, player2);
	engine->getGameMap()->assignOccupantToTerritory(8, player2);
	engine->getGameMap()->assignOccupantToTerritory(9, player2);
	engine->getGameMap()->assignOccupantToTerritory(10, player3);
	engine->getGameMap()->assignOccupantToTerritory(11, player3);
	engine->getGameMap()->assignOccupantToTerritory(12, player3);
	engine->getGameMap()->assignOccupantToTerritory(13, player3);
	engine->getGameMap()->assignOccupantToTerritory(14, player3);
	engine->getGameMap()->assignOccupantToTerritory(15, player4);
	engine->getGameMap()->assignOccupantToTerritory(16, player4);
	engine->getGameMap()->assignOccupantToTerritory(17, player4);
	engine->getGameMap()->assignOccupantToTerritory(18, player4);
	engine->getGameMap()->assignOccupantToTerritory(19, player4);
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(1));
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(2));
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(3));
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(4));
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(5));
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(6));
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(7));
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(8));
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(9));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(10));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(11));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(12));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(13));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(14));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(15));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(16));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(17));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(18));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(19));
	engine->getGameMap()->getTerritory(6)->addNumArmies(10);
	//setting initial army pool.
	player1->setArmyToBePlaced(10);
	player2->setArmyToBePlaced(10);
	player3->setArmyToBePlaced(10);//set to 5 to demonstrate failed deploy due to not enough armies
	player4->setArmyToBePlaced(10);
	//player1->issueOrder();
	//player2->issueOrder();
	//player3->issueOrder();
	//player4->issueOrder();
	engine->issueOrdersPhase();
	engine->executeOrdersPhase();
	//Player* player2 = new Player(2, "Neil");

	/*engine->startUpPhase();
	engine->mainGameLoop();*/
	delete engine;
	delete deck;

	return 0;
}

