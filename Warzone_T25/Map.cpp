#include "Map.h";
#include "string";
#include<iostream>

Territory::Territory(int id, std::string newName) : territoryId(id), territoryName(newName) {
	//left empty on purpose to demonstrate fancy constructor syntax =)
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
	std::cout << "map destroyed";
}
void Map::addTerritory(int id, std::string name) {
	Territory* newTerritory = new Territory(id, name);
	map.push_back(newTerritory);
}
void Map::printMap() {
	for (auto x : map) {
		std::cout << "Territory name: " << (*x).getName() << " " << "Territory ID: " << (*x).getTerritoryID() << std::endl;
	}
}