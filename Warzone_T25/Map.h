	#pragma once
#include"Player.h"
#include <string>
#include<vector>
#include<iostream>

using namespace std;

class Territory {

public:
	//constructors and destructors
	Territory();
	Territory(int id, std::string name, int continentID);
	Territory(const Territory &territory);
	Territory(int tId, Player* p, int numArmies, string tName, int continentId);
	~Territory();

	//getters
	int getTerritoryID();
	int getTerritoryContinentID();
	int getNumArmies();
	std::string getName();
	inline Player* getPlayer() { return player; }
	inline bool getIsVisited() { return isVisited; }
	inline int getNonCommitedArmies() { return nonComittedArmies; };
	vector<Territory*> getAdjacentTerritories();
	Player* getTerritoryOccupant();
	inline bool getWasAdvanced() { return wasAdvanced; }
	inline bool getIsAttacked() { return isAttacked; }

	//setters
	inline void setTerritoryID(int id) { territoryId = id; }
	void setTerritoryOccupant(Player*);
	void setTerritoryName(std::string name);
	void setNumArmies(int num);
	inline void setIsVisited(bool v) { isVisited = v; }
	inline void setNonCommitedArmies(int count) { nonComittedArmies = count; }
	inline void setWasAdvanced(bool adv) { wasAdvanced = adv; }
	inline void setIsAttacked(bool b) { isAttacked = b; }

	//Additional functions
	void addNumArmies(int);
	friend ostream& operator<<(ostream& outs, const Territory& theObject);
	Territory& operator= (const Territory& territory);
	void addAdjacentTerritory(Territory*);
	static bool compByArmyCount(Territory* a, Territory* b);
	static bool compByincomingArmies(Territory* a, Territory* b);
	static bool compById(Territory* a, Territory* b);
	inline void incNonCommitedArmies(int count) { nonComittedArmies += count; }
	inline void decNonCommitedArmies(int count) { nonComittedArmies -= count; }

	int incomingArmies;
private:
	int territoryId;
	Player* player;
	int numArmies;
	int nonComittedArmies;
	std::string territoryName;
	int territory_continentID;
	vector<Territory*> adjacentTerritories;
	bool isVisited = false;
	bool wasAdvanced = false;
	bool isAttacked = false;
};

class Continent {
public:
	Continent(int id, std::string name, int bonus);
	Continent();
	Continent(const Continent& continent);
	~Continent();
	//getters
	int getContinentID();
	int getBonus();
	std::string getContinentName();
	//setters
	void setContinentName(std::string name);
	void printContinent();
	//methods
	void addTerritoryToContinent(Territory* territory);
	std::vector<Territory*> getContinentTerritoryList();
	friend ostream& operator<<(ostream& outs, const Continent& theObject);
	Continent& operator= (const Continent& continent);
private:
	int bonus;
	std::string continentName;
	int continentId;
	std::vector<Territory*> continentTerritoryList;
};

class Map {
public:
	//constructors and destructors
	Map(std::string message);
	Map(const Map& map);
	~Map();
	//getters
	int getSize();
	std::vector<Continent*> getContinents();
	vector<std::vector<Territory*>> getMap() { return map; }
	Territory* getTerritory(int);
	bool validate();

	//methods
	void addTerritory(int id, std::string name, int continentID);
	void addContinent(int id, std::string name, int bonus);
	void addBorder(std::vector<int> borders);
	int assignOccupantToTerritory(int, Player*);
	void printMap();
	void printContinents();
	friend ostream& operator<<(ostream& outs, const Map& theObject);
	Map& operator= (const Map& continent);

	
private:
	std::vector<std::vector<Territory*>> map;
	std::vector<Continent*> continents;
	int size;

	//helper vectors
	std::vector<bool> visited;
	std::vector<bool> continentsVisited;
	
	//helper functions
	void dfs(int startNode, std::vector<std::vector<int>> adjacencyMatrix);
	void continentDfs(int startNode, std::vector<std::vector<int>> adjacencyMatrix);	
	std::vector<std::vector<int>> constructUnidirectionalMatrix();
	bool uniqueTerritory();
	bool isConnected();
	bool areContinentsConnected();
	int search(int);
};
namespace phase1_part_1{
	void start();
}

