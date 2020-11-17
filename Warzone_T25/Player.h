//IMPORTANT: assignment operator and copy constructor will do a shallow copy. duplicated player
// will point to the orginal objects, like Territory, Hand, Orders, cards or else it might break the game.
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
	bool isConquerer;
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
	inline bool getConquererFlag() { return isConquerer; }
	inline OrderList* getOrderList() { return orderlist;  }
	//Setters
	void setArmyToBePlaced(int count);
	void setConquererFlag(bool);
	void setOrderList(OrderList*);
	
	void addToArmiesToBePlaced(int);
	vector<Territory*> toDefend(); // returns list of territory pointers to defend
	vector<Territory*> toAttack();// returns list of territory pointers to defend
	void setPlayerHand(Hand*);
	void removeTerritoryFromList(int playerIndex);
	void sortOrderList();
	Order* getNextOrder();
	//functions
	void declareDiplomacy(Player* player);
	void clearDiplomacy();
	void addPlayerToDiplomacyList(int);
	vector<int> getDiplomacies();

	void assignTerritoryToPlayer(Territory* newTerritory);
	void issueOrder();// todo

};

namespace part_3 {

	void start();

}
