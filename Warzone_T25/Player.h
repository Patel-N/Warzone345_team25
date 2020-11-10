//IMPORTANT: assignment operator and copy constructor will only copy playerId,playerName,armyToBePlaced,
// or else we will have to duplicate territories objects, card objects, and order objects and might break the game

#pragma once
#include <iostream>
#include <list>
#include "Cards.h"
#include "Orders.h"
#include <string>


using namespace std;

class Territory;// forward declaration

class Player
{
private:
	vector<Territory*> territoryPtr; 
	Hand* handPtr;
	OrderList* orderlist;
	int playerId;
	string playerName;
	int armyToBePlaced;
	vector<int> diplomacy;//this member variable serves to add target players for the negotiate order


public:
	static Deck* common_deck;//static because the deck is a shared object among all players in game

	void issueOrder(Order* order) ;
	
	//Ctors
	Player(int,string,int);
	Player();
	//Dtors
	~Player();
	
	//Copy Ctor
	Player(const Player& input);
	
	//stream input
	friend istream& operator >> (istream& input, Player& obj);

	//stream output
	friend ostream& operator << (ostream& output, Player& obj);

	//assignment operator = overload
	Player& operator = (const Player& input);

	//Getters INLINE
	inline vector<Territory*> getPlayerTerritories() { return territoryPtr; }
	inline Hand* getPlayerHand() { return handPtr; };
	inline OrderList* getPlayerOrders() { return orderlist; }
	inline int getPlayerId() { return playerId; }
	inline string getPlayerName() { return playerName; }
	inline int getArmyToBePlaced() { return armyToBePlaced; };

	//Setters
	void setArmyToBePlaced(int count);
	void addToArmiesToBePlaced(int);
	vector<Territory*> toDefend(); // returns list of territory pointers to defend
	vector<Territory*> toAttack();// returns list of territory pointers to defend
	void setPlayerHand(Hand*);
	void removeTerritoryFromList(int playerIndex);
	Order* getNextOrder();
	//functions
	vector<Territory*> toDefend(); // todo
	vector<Territory*> toAttack();// todo
	void declareDiplomacy(int);
	void clearDiplomacy();
	vector<int> getDiplomacies();

	void assignTerritoryToPlayer(Territory* newTerritory);
	void issueOrder();// todo

};

namespace part_3 {

	void start();

}
