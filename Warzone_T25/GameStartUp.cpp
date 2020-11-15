#include "GameStartUp.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//constructor
GameStartUp::GameStartUp() { cout << "default GameStartup Constructor created" << endl; };
GameStartUp::GameStartUp(GameEngine* engine) {
	gameEngine = engine;
}

//functions
void GameStartUp::startUpPhase()
{
	//the purpose of this funtionc is to assign territory to players randomly in a round robin fashion, 
	//then assign army on those territory
	//implementation: 2 temp pointer vectors are made for player and territory poiting to the real objects, then shuffled, then assigned in a robin

	int numOfPlayers = gameEngine->getPlayers().size();
	int numOfTerritories = gameEngine->getGameMap()->getSize(); ;
	vector<Territory*> tempTerritoriesPtr(numOfTerritories);
	vector<Player*> tempPlayerPtr(numOfPlayers);

	for (int i = 0; i < numOfTerritories; i++) { // this makes the tempTerritoriesPtr point to the same territories as the orginal vector, shallow copy
		tempTerritoriesPtr[i] = gameEngine->getGameMap()->getTerritory(i+1);
	}

	srand(time(0));//part of random process
	std::random_shuffle(tempTerritoriesPtr.begin(), tempTerritoriesPtr.end());//shuffle only the pointers of temp array pointer

	for (int i = 0; i < numOfPlayers; i++) { //make this tempPlayerPtr point to the same players as the orginal vector, shallow copy
		tempPlayerPtr.at(i) = gameEngine->getPlayers().at(i);
	}
	srand(time(0));//part of random process
	std::random_shuffle(tempPlayerPtr.begin(), tempPlayerPtr.end());//shuffle only the pointers of temp array pointer

	
	for (int i = 0; i < numOfTerritories; i++) {//assign territories to players round robin fashion

		for (int j = 0; j < numOfPlayers; j++){
			cout << "territory: "<< i<<" :"<<tempTerritoriesPtr.at(i)->getName()<<endl;
			cout << "player: " << i << " :" << tempPlayerPtr.at(i)->getPlayerName() << endl;
			tempPlayerPtr.at(j)->assignTerritoryToPlayer(tempTerritoriesPtr.at(i));		
			i++;
			if (i <= numOfTerritories) { break; };
		}
	}
	cout << gameEngine->getPlayers().at(0)->getPlayerName() <<": " << gameEngine->getPlayers().at(0)->getPlayerTerritories().size() << endl;
	cout << gameEngine->getPlayers().at(1)->getPlayerName() << ": " << gameEngine->getPlayers().at(1)->getPlayerTerritories().size() << endl;
	cout << gameEngine->getPlayers().at(0)->getPlayerName()<<"  ter: "<<gameEngine->getPlayers().at(0)->getPlayerTerritories().at(0)->getName() << endl;

}
