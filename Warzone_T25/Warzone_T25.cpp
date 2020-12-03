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
	Deck* deck = new Deck();
	Player::common_deck = deck;
	Card* card1 = new Card(1);
	Card* card2 = new Card(2);
	Card* card3 = new Card(3);
	Card* card4 = new Card(4);
	Card* card5 = new Card(5);
	deck->addCardToDeck(card1);
	deck->addCardToDeck(card2);
	deck->addCardToDeck(card3);
	deck->addCardToDeck(card4);
	deck->addCardToDeck(card5);
	//part_1::start();  
	//part_2::start(); 
	//part_3::start();
    //part_4::start();
	//part_5::start();

	Player* player1 = new Player(1, "Neil",1,1);
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
	Card* card = new Card(1);
	player1->getPlayerHand()->addCardToHand(card3);
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
	engine->getGameMap()->getTerritory(7)->addNumArmies(5);
	engine->getGameMap()->getTerritory(8)->addNumArmies(5);
	//setting initial army pool.
	player1->setArmyToBePlaced(10);
	player2->setArmyToBePlaced(10);
	player3->setArmyToBePlaced(10);
	player4->setArmyToBePlaced(10);
	//player1->issueOrder();
	//player2->issueOrder();
	//player3->issueOrder();
	//player4->issueOrder();
	engine->issueOrdersPhase();
	engine->executeOrdersPhase();
	//Player* player2 = new Player(2, "Neil");
	return 0;
}

