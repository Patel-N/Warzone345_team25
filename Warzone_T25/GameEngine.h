#pragma once
#include<vector>
#include"Player.h"
#include"Map.h"
using namespace std;
class GameEngine {
public:
	GameEngine();

	GameEngine(Map* map);
	GameEngine(const GameEngine& engine);

	//Setters Getters
	void setGameMap(Map* map);


	Map* getGameMap();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void addPlayer(Player*);
	friend ostream& operator<<(ostream& outs, const GameEngine& theObject);
	GameEngine& operator= (const GameEngine& engine);

	//getters
	vector<Player*> getPlayers();

	void mainGameLoop();
private:
	vector<Player*> players;
	Map* game_map;

};
