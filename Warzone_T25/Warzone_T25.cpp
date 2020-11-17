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
	

	engine->startUpPhase();// assign territory to players randomly, give army to territory
	//engine->reinforcementPhase();


	//part_1::start();  
	//part_2::start(); // part_1 should be enabled with part_2
	//part_3::start();
//	part_4::start();
	//part_5::start();


}

