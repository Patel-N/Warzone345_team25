#pragma once
#include<vector>
#include"Player.h"
#include"Map.h"
#include "GameObservers.h"

using namespace std;
class GameEngine : public Subject {
public:
	//constructors
	GameEngine();

	GameEngine(Map* map);
	GameEngine(const GameEngine& engine);

	//Setters
	void setGameMap(Map* map);



	Map* getGameMap();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void addPlayer(Player*);
  void startUpPhase();// PART2 assign players territories in round robin, and give them armies in  int armyToBePlaced in player class
	friend ostream& operator<<(ostream& outs, const GameEngine& theObject);
	GameEngine& operator= (const GameEngine& engine);


	//getters
	vector<Player*> getPlayers();
	int getPhase();
	string getPName();
	Player* getConquerer();
	int getRounds();
	int getArmyCount();

	void mainGameLoop();
private:
	vector<Player*> players;
	Map* game_map;
	int phaseID;
	string pName;
	int armyPool;
	Player* conquerer;
	int totalRounds;
};

namespace part_3 {
	void start();
}
