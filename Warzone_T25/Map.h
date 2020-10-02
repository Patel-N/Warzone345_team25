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

class Map {
public:
	//constructors and destructors
	Map(std::string message);
	~Map();

	//methods
	void addTerritory(int id, std::string name);
	void printMap();

private:
	std::vector<Territory*> map;

};

