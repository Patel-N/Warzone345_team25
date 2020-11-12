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
	std::string getName();
	inline Player* getPlayer() { return player; }
	inline int getNumArmies() { return numArmies; }
	vector<Territory*> getAdjacentTerritories();

	//setters
	void setTerritoryID(int id);
	void setTerritoryOccupant(Player*);
	void setTerritoryName(std::string name);
	inline void setNumArmies(int num) { numArmies = num; }
	

	friend ostream& operator<<(ostream& outs, const Territory& theObject);
	Territory& operator= (const Territory& territory);
	void addAdjacentTerritory(Territory*);

private:
	int territoryId;
	Player* player;
	int numArmies;
	std::string territoryName;
	int territory_continentID;
	vector<Territory*> adjacentTerritories;
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
namespace part_1{
	void start();
}


//DOUBLY LINKED LIST IMPLEMENTATION FOR TERRITORY
class Node {
private:
	Territory* sourceTerri;
	Territory* targetTerri;
	int listsize;

public:
	//Ctors	
	Node();
	Node(Territory* sT, Territory* tT);

	//Dtor
	~Node();

	//Getters
	inline Territory* getSourceTerritory() { return sourceTerri; };
	inline Territory* getTargetTerritory() { return targetTerri; };

	Node* prev = NULL;
	Node* next = NULL;
	void addBefore(Territory* t, Node* n);
	void addAfter(Territory* t, Node* n);
	inline void incrementSize() { listsize++; };
	inline int size() { return listsize; };

};