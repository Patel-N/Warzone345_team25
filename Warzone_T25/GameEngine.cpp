#include "GameEngine.h"
#include<iostream>
#include <algorithm>

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
	cout << endl << "HERREEEE************" << endl;
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


//**PART 2 DELIVERY**
void GameEngine::startUpPhase()
{
	//the purpose of this funtionc is to assign territory to players randomly in a round robin fashion, 
	//then give players armies in armyToBePlaced
	//implementation: 1 temp pointer vectors are made for territory poiting to the real objects, then shuffled, then assigned in a robin
	//** for delivery 2, theres also code to demonstrate functionality  output
	int numOfPlayers = getPlayers().size();
	int numOfTerritories = getGameMap()->getSize(); ;
	vector<Territory*> tempTerritoriesPtr(numOfTerritories); // the temp territory to help with the random round robin
	int numOfArmieToBePlaced = 0;// this is the number of armies to to be placed in the reinforcement pool for each player

	for (int i = 0; i < numOfTerritories; i++) { // this makes the tempTerritoriesPtr point to the same territories as the orginal vector, shallow copy
		tempTerritoriesPtr[i] = getGameMap()->getTerritory(i + 1);
	}

	srand(time(0));//part of random process
	std::random_shuffle(tempTerritoriesPtr.begin(), tempTerritoriesPtr.end());//shuffle only the pointers of temp array pointer

	for (int i = 0; i < numOfTerritories; i++) {//assign territories to players round robin fashion

		for (int j = 0; j < numOfPlayers; j++) {// for the number of players, at the players array and give them territories from the temp terry array that was shuffled randomly
			getPlayers().at(j)->assignTerritoryToPlayer(tempTerritoriesPtr.at(i));
			i++;
			if (i >= numOfTerritories) { break; };
		}
	}

	for (int i = 0; i < numOfTerritories; i++) { //gettign rid of dangling pointers if ever territories in the future get deleted for some reason
		tempTerritoriesPtr[i] = NULL;
	}


	switch (numOfPlayers) {//setting up numOfArmieToBePlaced depending on numOfPlayers
	case 2:
		numOfArmieToBePlaced = 40;
		break;
	case 3:
		numOfArmieToBePlaced = 35;
		break;
	case 4:
		numOfArmieToBePlaced = 30;
		break;
	case 5:
		numOfArmieToBePlaced = 25;
		break;

	default:
		cout << "error in case statement in GameStartUp.ccp. Player int armyToBePlaced was not initialized" << endl;
		break;
	}


	for (int i = 0; i < numOfPlayers; i++) {// assign int armyToBePlaced 
		getPlayers().at(i)->setArmyToBePlaced(numOfArmieToBePlaced);
	}
	cout << endl;
	cout << "cout from GameEngine.cpp, startUpPhase()" << endl;
	if (numOfPlayers == 0) { cout << "there are no players in the game engine" << endl; }
	for (int i = 0; i < numOfPlayers; i++) {// demonstration for delivery output
		
		cout <<getPlayers().at(i)->getPlayerName() << " owns: " << endl;//output playername
		cout << "  reinforcement pool: " <<getPlayers().at(i)->getArmyToBePlaced() << endl;//output reinforment pool
		for (int j = 0; j < getPlayers().at(i)->getPlayerTerritories().size(); j++) {
			cout <<"  "<< getPlayers().at(i)->getPlayerTerritories().at(j)->getName()<<endl;//output territories
		}
		cout << endl;
	}
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

