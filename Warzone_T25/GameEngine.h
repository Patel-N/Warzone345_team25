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
	void startUpPhase();// assign players territories in round robin, and give them armies in  int armyToBePlaced in player class

private:
	vector<Player*> players;
	Map* game_map;
};