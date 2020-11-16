#pragma once
#include<vector>
#include"Player.h"
#include"Map.h"
using namespace std;
class GameEngine {
public:
	GameEngine();

	GameEngine(Map* map);

	//Setters Getters
	void setGameMap(Map* map);


	Map* getGameMap();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void addPlayer(Player*);
	friend ostream& operator<<(ostream& outs, const GameEngine& theObject);

	//getters
	vector<Player*> getPlayers();
private:
	vector<Player*> players;
	Map* game_map;

};
