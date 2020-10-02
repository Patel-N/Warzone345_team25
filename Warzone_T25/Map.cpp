#include "Map.h";
#include "string";
#include<iostream>

Territory::Territory(int id, std::string newName) : territoryId(id), territoryName(newName) {
	//left empty on purpose to demonstrate fancy constructor syntax =)
}
Territory::~Territory() {
	//std::cout << "territory destroyed";
}
std::string Territory::getName() {
	return territoryName;
}
int Territory::getTerritoryID() {
	return territoryId;
}
Map::Map(std::string message) {
	std::cout << message;
}
Map::~Map() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			delete map[i][j];
		}
	}
	std::cout << "map destroyed";
}
void Map::addTerritory(int id, std::string name) {
	Territory* newTerritory = new Territory(id, name);
	std::vector<Territory*> temp;
	temp.push_back(newTerritory);
	map.push_back(temp);
}
void Map::addBorder(std::vector<int> borders) {
	int territoryID = borders.at(0);
	for (int i = 1; i < borders.size(); i++) {
		map.at(territoryID - 1).push_back(map.at(borders.at(i) - 1).at(0));
	
	}
}
void Map::printTerritoryList() {
	for (auto x :territoryList) {
		std::cout << "Territory name: " << (*x).getName() << " " << "Territory ID: " << (*x).getTerritoryID() << std::endl;
	}
}
void Map::printMap() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			Territory temp = *map[i][j];
			std::cout << temp.getTerritoryID();
		}
		std::cout << std::endl;
	}
}