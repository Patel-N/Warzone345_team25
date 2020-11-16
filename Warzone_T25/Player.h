#pragma once
#include <iostream>
#include <list>
#include "Cards.h"
#include "Orders.h"
#include <string>

using namespace std;

class Territory;
class TerritoryAttackDefend;

class Player
{
private:
	vector<Territory*> territoryPtr; 
	Hand* handPtr;
	vector<Order*> orderPtr;
	int playerId;
	string playerName;
	int armyToBePlaced;
	vector<Territory*> getPlayerAdjcentTerritories();
	int nonCommitedArmy;


public:
	void issueOrder() ;
	
	//Ctors
	Player(int id, string name, vector<Territory*> ownedT, Hand* h, vector<Order*> o, int armyCount);
	Player(int,string);
	Player();
	
	//Dtors
	~Player();

	//Copy Ctor
	Player(const Player& input);
	
	friend ostream& operator << (ostream& output, Player& obj);

	friend istream& operator >> (istream& input, Player& obj);


	//Getters
	inline vector<Territory*> getPlayerTerritories() { return territoryPtr; }
	inline Hand* getPlayerHand() { return handPtr; };
	inline vector<Order*> getPlayerOrders() { return orderPtr; }
	inline int getPlayerId() { return playerId; }
	inline string getPlayerName() { return playerName; }
	inline int getArmyToBePlaced() { return armyToBePlaced; };
	inline int getNonComitedArmy() { return nonCommitedArmy; }

	//Setters
	void setArmyToBePlaced(int count);
	inline void setNonComitedArmy(int count) { nonCommitedArmy = count; }

	vector<Territory*> toDefend(); // returns list of territory pointers to defend
	vector<Territory*> toAttack();// returns list of territory pointers to defend

	void assignTerritoryToPlayer(Territory* newTerritory);
	vector<Territory*> allTerritoryVectorBuilder(Territory* origin);

	//assignment operator overload
	Player& operator = (const Player& input);
};


namespace part_3 {

	void start();

}
