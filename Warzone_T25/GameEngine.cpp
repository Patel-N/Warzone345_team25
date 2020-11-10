#include "GameEngine.h"
#include<iostream>

using namespace std;

GameEngine::GameEngine(){
	cout << "Game Engine Created";
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
				isContinentIdChecked = ( cId == continentChecked[j]) ? true : false;
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
	}
	

}

void GameEngine::issueOrdersPhase(){

}

void GameEngine::executeOrdersPhase(){
	vector<int> allOrdersFinished;
	for (int i = 0; i < players.size(); i++) {
		allOrdersFinished.push_back(1);
	}
	bool terminateExecution = false;
	while (!terminateExecution) {
		terminateExecution = true;
		for (int i = 0; i < players.size(); i++) {
			if (allOrdersFinished[i] == 1) { terminateExecution = false; }
		}
		for (int i = 0; i < players.size(); i++) {
			//when all payers have no more orders to execute, areAllOrdersExecuted will become true. if only one 
			//player still has orders, it will set the variable to false 
			if (players[i]->getPlayerOrders().size() == 0) {
				allOrdersFinished[i] = 0;
			}
			else {
				Order* candidateOrder = players[i]->getNextOrder();
				candidateOrder->execute(i);
			}
		}
	}
	for (int i = 0; i < players.size(); i++) {
		players[i]->clearDiplomacy();
	}
}

void GameEngine::addPlayer(Player* player) {
	players.push_back(player);
}

ostream& operator<<(ostream& outs, const GameEngine& theObject) {
	outs
		<< "==================================" << endl
		<< "        WELCOME TO WARZONE        " << endl
		<< "==================================" << endl;
	if (theObject.players.size() > 0) {
		outs
			<< "=======================" << endl
			<< "      Game Players     " << endl
			<< "=======================" << endl;
		for (int i = 0; i < theObject.players.size(); i++) {
			outs
				<< *theObject.players[i] << endl;
		}
	}
	else {
		outs
			<< "There are no players in the game yet" << endl;
	}

	return outs;
}
