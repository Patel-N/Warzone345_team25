#pragma once
#include<vector>
#include"Player.h"
#include"Map.h"
using namespace std;
class GameEngine {
public:
	//constructors
	GameEngine();
	GameEngine(Map* map);

	//Setters
	void setGameMap(Map* map);
	void addPlayer(Player*);

	//getters
	Map* getGameMap();
	vector<Player*> getPlayers();


	//functions
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	

private:
	vector<Player*> players;
	Map* game_map;
};