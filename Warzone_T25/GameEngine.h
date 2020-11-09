#pragma once
#include<vector>
#include"Player.h"
using namespace std;
class GameEngine {
public:
	GameEngine();
	void reinforcementPhase();
	void issueOrdersPhase();
	void executeOrdersPhase();
	void addPlayer(Player*);
private:
	vector<Player*> players;

};