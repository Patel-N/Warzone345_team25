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



		part_1::start();

	
		//creating game engine, creating map, loading canada map
		MapLoader * loader = new MapLoader();
	Map* map = (loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);
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
	engine->startUpPhase();
	engine->mainGameLoop();
	delete engine;
	delete deck;
		return 0;
}