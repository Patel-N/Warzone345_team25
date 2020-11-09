#include "GameEngine.h"
#include<iostream>

using namespace std;

GameEngine::GameEngine(){
	cout << "Game Engine Created";
}

void GameEngine::reinforcementPhase(){}

void GameEngine::issueOrdersPhase(){}

void GameEngine::executeOrdersPhase(){}

void GameEngine::addPlayer(Player* player) {
	players.push_back(player);
}