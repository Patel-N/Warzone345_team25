#include "Part2Driver.h"
#include <iostream>
#include "MapLoader.h"
#include "GameEngine.h"
using namespace std;


void part_2::start()
{
	MapLoader* loader = new MapLoader();
	Map* map;
	map = new Map(loader->generateMap("./MapFiles/canada.map"));

	GameEngine* engine = new GameEngine(map);
	Player* player1 = new Player(1, "Yas", 0);
	Player* player2 = new Player(2, "Yas2", 0);
	Player* player3 = new Player(3, "Yas3", 0);
	Player* player4 = new Player(4, "Yas4", 0);
	Player* player5 = new Player(5, "Yas5", 0);
	engine->addPlayer(player1);
	engine->addPlayer(player2);
	engine->addPlayer(player3);
	engine->addPlayer(player4);
	engine->addPlayer(player5);
	engine->startUpPhase();// assign territory to players randomly, give army to territory
}
