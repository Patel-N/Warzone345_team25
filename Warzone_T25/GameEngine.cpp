#include "GameEngine.h"
#include<iostream>

using namespace std;

GameEngine::GameEngine() {
	cout << "Game Engine Created\n";
}

GameEngine::GameEngine(Map* map)
{
	game_map = map;
}

void GameEngine::setGameMap(Map* map)
{
	game_map = map;
}

Map* GameEngine::getGameMap()
{
	return game_map;
}

vector<Player*> GameEngine::getPlayers()
{
	return players;
}

void GameEngine::reinforcementPhase()
{
	//Loop through players
	for (int i = 0; i < players.size(); i++) {
		cout << endl << "Checking for player: " << players[i]->getPlayerName() << endl;
		int armyCount = 3;

		//Army calculation based on territories
		int territoryOwnedCount = (players[i])->getPlayerTerritories().size();
		armyCount += floor(territoryOwnedCount / 3);

		//Determine if player controls a full continent
		vector<Territory*> playerTerritories = (players[i])->getPlayerTerritories();
		vector<int> continentChecked;
		for (int z = 0; z < playerTerritories.size(); z++) {
			Territory* t = playerTerritories[z];
			bool isContinentIdChecked = false;
			int cId = t->getTerritoryContinentID();
			//Check if continent id is not found in vector
			for (int j = 0; j < continentChecked.size(); j++) {
				isContinentIdChecked = (cId == continentChecked[j]) ? true : false;
			}

			//Skip if continentId has already been checked
			if (!isContinentIdChecked) {
				//Add the continentId to the checked vector
				continentChecked.push_back(cId);

				Continent* targetedContinent = game_map->getContinents()[cId - 1];
				vector<Territory*> continentTerritories = targetedContinent->getContinentTerritoryList();
				int sameTerritoryCount = 0;

				//Loop through players territories 
				for (int j = 0; j < playerTerritories.size(); j++) {
					//cout << "print 5 times" << endl;
					for (int k = 0; k < continentTerritories.size(); k++) {

						//If a territory owned by the player is on the continent increment count

						if (playerTerritories[j]->getTerritoryID() == continentTerritories[cId]->getTerritoryID()) {
							sameTerritoryCount++;
						}

					}
				}

				//If sameTerritoryCount is equal to continent territory count then players owns all continent
				if (sameTerritoryCount == continentTerritories.size()) {
					armyCount += targetedContinent->getBonus();
				}
			}

		}
		cout << players[i]->getPlayerName() << " will get " << armyCount << " new units." << endl;
		players[i]->setArmyToBePlaced(armyCount);
		Notify();
	}

}

void GameEngine::issueOrdersPhase() {

}

void GameEngine::executeOrdersPhase() {}

void GameEngine::addPlayer(Player* player) {
	players.push_back(player);
}

//void GameEngine::Attach(Observer* o) {
//	_observers->push_back(o);
//};
//
//void GameEngine::Detach(Observer* o) {
//	_observers->remove(o);
//};
//
//void GameEngine::Notify() {
//	list<Observer*>::iterator i = _observers->begin();
//	for (; i != _observers->end(); ++i)
//		(*i)->Update();
//};