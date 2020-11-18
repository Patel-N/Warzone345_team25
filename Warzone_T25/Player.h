//IMPORTANT: assignment operator and copy constructor will only copy playerId,playerName,armyToBePlaced,
// or else we will have to duplicate territories objects, card objects, and order objects and might break the game

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
	vector<Territory*> territoryPtr; 
	Hand* handPtr;
	OrderList* orderlist;
	int playerId;
	string playerName;
	int armyToBePlaced;
	vector<Territory*> getPlayerAdjacentTerritories();
	bool isCommited = false;
	bool isConquerer;
	vector<int> diplomacy;//this member variable serves to add target players for the negotiate order
	void deployCreation(vector<Territory*> playerWeakestTerritories, int armyCount);
	bool defenseApplied = false;
	bool attackApplied = false;
	bool isCardPlayed = false;


public:
	static Deck* common_deck;//static because the deck is a shared object among all players in game

	void issueOrder(Order* order) ;
	
	//Ctors
	Player(int id, string name, vector<Territory*> ownedT, Hand* h, vector<Order*> o, int armyCount);
	Player(int,string);
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
	inline bool getIsCommited() { return isCommited; }
	inline bool getConquererFlag() { return isConquerer; }
	inline OrderList* getOrderList() { return orderlist; }
	inline bool getDefenseApplied() { return defenseApplied; }
	inline bool getAttackApplied() { return attackApplied; }
	inline bool getIsCardPlayed() { return isCardPlayed; }

	//Setters
	void setArmyToBePlaced(int count);
	inline void setIsCommited(bool com) { isCommited = com; }
	void setConquererFlag(bool);
	void setOrderList(OrderList*);
	inline void setDefenseApplied(bool b) { defenseApplied = b; }
	inline void setAttackApplied(bool b) { attackApplied = b; }
	void addToArmiesToBePlaced(int);
	void setPlayerHand(Hand*);
	void removeTerritoryFromList(int playerIndex);
	void sortOrderList();
	Order* getNextOrder();
	inline void setIsCardPlayed(bool b) { isCardPlayed = b; }

	//functions
	void declareDiplomacy(Player* player);
	void clearDiplomacy();
	void addPlayerToDiplomacyList(int);
	vector<int> getDiplomacies();
	vector<Territory*> toDefend(); // returns list of territory pointers to defend
	vector<Territory*> toAttack();// returns list of territory pointers to defend

	void assignTerritoryToPlayer(Territory* newTerritory);
	vector<Territory*> allTerritoryVectorBuilder(Territory* origin);
	void issueOrder();
};

namespace part_3 {

	void start();

}
