#pragma once
#include<vector>
#include"Player.h"
#include"Map.h"
#include "GameObservers.h"
using namespace std;

class GameEngine : public Subject {
public:
	GameEngine();
	GameEngine(Map* map);

	//Setters Getters
	void setGameMap(Map* map);

	Map* getGameMap();
	vector<Player*> getPlayers();

	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void addPlayer(Player*);

	//void Attach(Observer* o);
	//void Detach(Observer* o);
	//void Notify();

private:
	vector<Player*> players;
	Map* game_map;
};