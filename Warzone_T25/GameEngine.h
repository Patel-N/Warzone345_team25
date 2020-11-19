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

	void mainGameLoop();
private:
	vector<Player*> players;
	Map* game_map;

};

namespace part_3 {
	void start();
}
