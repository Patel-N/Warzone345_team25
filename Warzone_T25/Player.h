#pragma once
#include <iostream>
#include <list>
#include "Cards.h"
#include "Orders.h"
#include <string>

using namespace std;

class Territory;

class Player
{
private:
	vector<Territory*> territoryPtr; //BUG** TO DO
	Hand* handPtr;
	vector<Order*> orderPtr;
	int playerId;
	string playerName;

public:
	void issueOrder() ;
	
	//Ctors
	Player(int,string);
	Player();
	
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

	vector<Territory*> toDefend(); // returns list of territory pointers to defend

	vector<Territory*> toAttack();// returns list of territory pointers to defend

	void assignTerritoryToPlayer(Territory* newTerritory);

	//assignment operator overload
	Player& operator = (const Player& input);
};


namespace part_3 {

	void start();

}
