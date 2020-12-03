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
	cout << "//=======================================//\n";
	cout << "		Creating Map\n";
	cout << "//=======================================//\n";
	SelectMap* selectmap = new SelectMap();
	//creating game engine, creating map
	GameEngine* engine = new GameEngine();

	selectmap->printGameMaps();
	selectmap->setMap(); // choose swiss.map to check the case of invalid map
	engine->setGameMap(selectmap->loadmap());


	cout << "//=======================================//\n";
	cout << "		Creating Players\n";
	cout << "//=======================================//\n";
	SelectPlayers* selectplayers = new SelectPlayers();
	selectplayers->setnumPlayers();
	engine->setPlayers(selectplayers->createPlayers());
	cout << "\n\n";

	//=============Adding DecK===============//
	cout << "===========================\n";
	cout << " Adding cards to Deck\n";
	cout << "===========================\n";
	Deck* deck = new Deck();
	Player::common_deck = deck;
	for (int i = 1; i <= 25; i++) {
		Card* card = new Card(rand() % 5 + 1);
		card->set_type(rand() % 5 + 1);
		deck->addCardToDeck(card);
	}
	
	engine->startUpPhase();
	engine->mainGameLoop();
	delete engine;
	delete deck;
	return 0;
}