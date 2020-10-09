#pragma once
#include <string>
#include<vector>
class Territory {

public:
	//constructors and destructors
	Territory(int id, std::string name);
	Territory();
	~Territory();
	//getters
	int getTerritoryID();
	int* getPlayer();
	std::string getName();
	//setters
	void setTerritoryID(int id);
	void setPlayer(int&);
	void setTerritoryName(std::string name);

private:
	int territoryId;
	int* player;
	std::string territoryName;

};

class Continent {
public:
	Continent(int id, std::string name, int bonus);
	Continent();
	~Continent();
	//getters
	int getContinentID();
	int getBonus();
	std::string getContinentName();
	void printContinent();
	//methods
	void addTerritoryToContinent(Territory* territory);
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
	~Map();
	int getSize();

	//methods
	void addTerritory(int id, std::string name, int continentID);
	void addContinent(int id, std::string name, int bonus);
	void addBorder(std::vector<int> borders);
	void printMap();
	void printContinents();
	bool isConnected();



private:
	std::vector<std::vector<Territory*>> map;
	std::vector<bool> visited;
	void dfs(int startNode, std::vector<std::vector<int>> adjacencyMatrix);
	int size;
	std::vector<std::vector<int>> constructUnidirectionalMatrix();
	std::vector<Continent*> continents;

};
