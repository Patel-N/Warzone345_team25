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

GameEngine::GameEngine(const GameEngine& engine) {
	cout << endl << "In engine Copy Constructor" << endl;
	if (this != &engine) {
		*this = engine;
	}
}
//the game engine copy constructor copies everything in the original engine except for orders. orders are unique to players and copying the
//engine will reset all player orders
GameEngine& GameEngine::operator=(const GameEngine& originalEngine) {
	cout << endl << "In engine assignment operator" << endl;
	//using map deep copy constructor
	Map* map = new Map(*originalEngine.game_map);
	this->setGameMap(map);	
	//using player deep copy constructors. side node: the player copy constructor does not copy player territories or orders
	vector<Player*>ogPlayerVec = originalEngine.players;
	//looping through all original players and adding territories based on their previous list and adding cards in hand based on their previous hands
	for (int i = 0; i < ogPlayerVec.size(); i++) {
		Player* player = new Player(*ogPlayerVec[i]);
		this->addPlayer(player);
		Player* ogPlayer = ogPlayerVec[i];
		if (ogPlayer->getPlayerTerritories().size() > 0) {
			vector<Territory*>ogPlayerTerritoryVec = ogPlayer->getPlayerTerritories();
			for (int j = 0; j < ogPlayerTerritoryVec.size(); j++) {
				int ogTerritoryId = ogPlayerTerritoryVec[j]->getTerritoryID();
				this->game_map->assignOccupantToTerritory(ogTerritoryId, player);
				player->assignTerritoryToPlayer(this->game_map->getTerritory(ogTerritoryId));
			}
		}
		if (ogPlayer->getPlayerHand() != NULL && ogPlayer->getPlayerHand()->getCardsInHand().size() > 0) {
			Hand* hand = new Hand(*ogPlayer->getPlayerHand());
		}
		else {
			Hand* hand = NULL;
			player->setPlayerHand(hand);
		}
		//setting orderlists objects to null
		OrderList* orderlist = NULL;
		player->setOrderList(orderlist);
	}
	return *this;	
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

void GameEngine::mainGameLoop() {
	
	int round = 1;

	while (players.size() != 1) {
		
		cout << "******************** ROUND " << round << " ********************" << endl;
		reinforcementPhase();
		issueOrdersPhase();
		executeOrdersPhase();

		vector<Player*> activePlayers;
		
		for (int i = 0; i < players.size(); i++) {

			if (players[i]->getPlayerTerritories().size() != 0) {
				activePlayers.push_back(players[i]);
			}
			else {
				cout << "Player => " << players[i]->getPlayerName() << " has been eliminated." << endl;
			}

		}

		players = activePlayers;
		round++;
	
	}

}

void GameEngine::reinforcementPhase()
{
	//Loop through players
	for (int i = 0; i < players.size(); i++) {
		cout << endl << "Checking for player: " << players[i]->getPlayerName() << endl;
		int armyCount = 3;
		players[i]->addToArmiesToBePlaced(3);

		//Army calculation based on territories
		int territoryOwnedCount = (players[i])->getPlayerTerritories().size();
		armyCount += floor(territoryOwnedCount / 3);
		players[i]->addToArmiesToBePlaced(floor(territoryOwnedCount / 3));


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
					players[i]->addToArmiesToBePlaced(targetedContinent->getBonus());
				}
			}

		}
		cout << players[i]->getPlayerName() << " will get an additional " << armyCount << " new units." << endl;
		
	}

}

void GameEngine::issueOrdersPhase(){

	//Update nonCommitedArmies count for all players;
	for (int i = 0; i < players.size(); i++) {
		
		vector<Territory*> playerT = players[i]->getPlayerTerritories();

		for (int j = 0; j < playerT.size(); j++) {
			playerT[j]->setNonCommitedArmies(playerT[j]->getNumArmies());
			//cout << "Noncommit => " << playerT[j]->getNonCommitedArmies() << " || Current => " << playerT[j]->getNumArmies()  << endl;
		}

	}

	//Loop through players
	int commitedPlayersCount = 0;
	int index = 0;
	
	while (commitedPlayersCount != players.size()) {
		
		
		//Player can't be commited already
		if (!players[index]->getIsCommited()) {
			players[index]->issueOrder();

			//Check if last order is a commit
			if (players[index]->getOrderList()->allOrders.size() > 0 && players[index]->getOrderList()->peekLastOrder() == "Commit") {
				cout << "Player " << players[index]->getPlayerName() << " has commited their turn." << endl;
				commitedPlayersCount++;
				players[index]->setIsCommited(true);
			}
		}

		index++;

		//Reset index for round robin
		if (index == players.size())
			index = 0;
	}

	//Reset territories & Player bools && remove commit
	for (int i = 0; i < players.size(); i++) {
		
		players[i]->getOrderList()->remove(players[i]->getOrderList()->numSize);

		//set attack/defense/card to false
		players[i]->setDefenseApplied(false);
		players[i]->setAttackApplied(false);
		players[i]->setIsCardPlayed(false);
		players[i]->setIsCommited(false);

		if (i == 0) {
			
			//Reset toAttack territories
			vector<Territory*> attackableT = players[i]->toAttack();
			for (int j = 0; j < attackableT.size(); j++) {
				attackableT[j]->setWasAdvanced(false);
				attackableT[j]->setIsAttacked(false);
			}

			//Reset toAttack territories
			vector<Territory*> defendableT = players[i]->toDefend();
			for (int j = 0; j < defendableT.size(); j++) {
				defendableT[j]->setWasAdvanced(false);
				defendableT[j]->setIsAttacked(false);
			}

		}
	}

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
			if (players[i]->getPlayerOrders()->allOrders.size() == 0) {
				allOrdersFinished[i] = 0;
			}
			else {
				Order* candidateOrder = players[i]->getNextOrder();
				candidateOrder->execute(i);
				players[i]->getPlayerOrders()->remove(1);
				//delete candidateOrder;//this order will no longer be reused after execution and it iis safe to delete it.
			}
		}
	}
	for (int i = 0; i < players.size(); i++) {
		players[i]->clearDiplomacy();
		players[i]->setConquererFlag(false);//conquererFlag is the variable that determines whether the player conquered or not a territory during a turn
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
			if (theObject.players[i] == NULL) {
				outs << endl << "NULL PLAYER" << endl;
			}
			else {
				outs
					<< endl << *theObject.players[i] << endl;
			}
		}
	}
	else {
		outs
			<< "There are no players in the game yet" << endl;
	}

	return outs;
}
