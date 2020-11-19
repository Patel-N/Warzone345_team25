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

	while (players[0]->getPlayerTerritories().size() != game_map->getSize()) {

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

	cout << endl << "*********************GAME IS OVER*********************" << endl;
	cout << endl << "This game took " << round << " rounds!" << endl;
	cout << endl<<"Congrats " << players[0]->getPlayerName() << " YOU WON!!"<<endl;
	cout << endl << players[0]->getPlayerName() << " has conquered " << players[0]->getPlayerTerritories().size() << endl;
}

void GameEngine::reinforcementPhase()
{
	cout << "REINFORCEMENT PHASE:" << endl;

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

					for (int k = 0; k < continentTerritories.size(); k++) {
					
						//If a territory owned by the player is on the continent increment count
						if (playerTerritories[j]->getTerritoryID() == continentTerritories[k]->getTerritoryID()) {
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
	cout << endl << "ISSUE ORDER PHASE:" << endl << endl;

	//Update nonCommitedArmies count for all players;
	for (int i = 0; i < players.size(); i++) {
		vector<Territory*> playerT = players[i]->getPlayerTerritories();

		for (int j = 0; j < playerT.size(); j++) {
			playerT[j]->setNonCommitedArmies(playerT[j]->getNumArmies());
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


//**PART 2 DELIVERY**
void GameEngine::startUpPhase()
{
	//the purpose of this funtionc is to assign territory to players randomly in a round robin fashion, 
	//then give players armies in armyToBePlaced
	//implementation: 1 temp pointer vectors are made for territory poiting to the real objects, then shuffled, then assigned in a robin
	// also for delivery 2, since i dont work with part1 for the demo and provide my own territories and players, i shuffle the player  list, to satisfy "The order of play of the players in the game is determined randomly"
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


	//**SHUFFLING THE PLAYER LIST FOR DELIVERY 2, to satisfy "The order of play of the players in the game is determined randomly"
	srand(time(0));//part of random process
	std::random_shuffle(players.begin(), players.end());//shuffle only the pointers of temp array pointer


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

