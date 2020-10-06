#include "Map.h";
#include "string";
#include<iostream>;
#include<stack>;

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
Continent::Continent(int id, std::string name, int bonus) : continentId(id), continentName(name), bonus(bonus) {
	//left empty on purpose to demonstrate fancy constructor syntax =)
}
int Continent::getContinentID() {
	return continentId;
}
std::string Continent::getContinentName() {
	return continentName;
}
int Continent::getBonus() {
	return bonus;
}
void Continent::printContinent() {
	std::cout << "Continent Name: " << continentName << " ID# " << continentId << "bonus = " << bonus;
	std::cout << std::endl;
	std::cout << "Territory list: " << std::endl;
	if (continentTerritoryList.size() > 0) {
		for (auto x : continentTerritoryList) {
			std::cout << x->getTerritoryID() << " ";
		}
		std::cout << std::endl;
	}
}
void Continent::addTerritoryToContinent(Territory* territory) {
	if (continentTerritoryList.size() == 0) {
		std::cout << "in here";
		continentTerritoryList.push_back(territory);
	}
	else {
		int i = continentTerritoryList.size() - 1;
		bool didLoop = false;
		while ((*territory).getTerritoryID() < (*continentTerritoryList[i]).getTerritoryID()) {
			didLoop = true;//this is to take care of special case where you insert a the end
			i--;
			if (i < 0) {
				break;
			}
		}
		if (didLoop) {
			int increment = i + 1;
			continentTerritoryList.insert(continentTerritoryList.begin() + increment, territory);
		}
		else {
			continentTerritoryList.push_back(territory);
		}
	}
}
Map::Map(std::string message) {
	std::cout << message;
}
Map::~Map() {
	std::cout << "map destroyed";
}
void Map::addContinent(int id, std::string name, int bonus) {
	Continent* continent = new Continent(id, name, bonus);
	if (continents.size() == 0) {
		continents.push_back(continent);
	}
	else {
		int i = continents.size() - 1;
		bool didLoop = false;
		while (id < continents[i]->getContinentID()) {
			didLoop = true;//this is to take care of special case where you insert a the end
			i--;
			if (i < 0) {
				break;
			}
		}
		if (didLoop) {
			int increment = i + 1;
			continents.insert(continents.begin() + increment, continent);
		}
		else {
			continents.push_back(continent);
		}
	}
	
}
/*The addTerritory method will not only add a territory but also insert it such that
the map vector remains sorted in increasing order*/
void Map::addTerritory(int id, std::string name,int continentID) {
	Territory* newTerritory = new Territory(id, name);
	if (continents.size() >= continentID) {
		continents[continentID - 1]->addTerritoryToContinent(newTerritory);
	}
	std::vector<Territory*> temp;
	temp.push_back(newTerritory);
	if (map.size() == 0) { 
		map.push_back(temp); 
	}
	else {
		int i = map.size() - 1;
		bool didLoop = false;
		while (id < map[i][0]->getTerritoryID()) {
			didLoop = true;//this is to take care of special case where you insert a the end
			i--;
			if (i < 0) {
				break;
			}
		}
		//todo: check for duplicate ids
		if (didLoop) {
			std::cout << "in loop i = " << i;
			int increment = i + 1;
			map.insert(map.begin() + increment, temp); // i is the value where we stop so we want to insert after that value hence the +1. if we want to insert at begining 
			//i will end at -1. we do -1 + 1 =0. We then insert at 0
		}
		else {
			map.push_back(temp);
		}
	}
	size++;
}
int Map::getSize() {
	return size;
}
void Map::addBorder(std::vector<int> borders) {
	int territoryID = borders.at(0);
	for (int i = 1; i < borders.size(); i++) {
		map.at(territoryID - 1).push_back(map.at(borders.at(i) - 1).at(0));
	
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
void Map::printContinents() {
	std::cout << "Continents details: " << std::endl;
	if (continents.size() > 0) {
		for (auto x : continents) {
			x->printContinent();
		}
	}
}
bool Map::isConnected() {
	/*This method will first construct a unidirectional graph. to determine if a directed graph is at least weakly connected, we first assume the edges are
	unidirectional. then , frim any arbitrary node in G, we must be able to reach any node in G.*/
	std::vector<std::vector<int>> adjacencyMatrix = constructUnidirectionalMatrix();
	//boolean vector set to false as in no nodes have been visited yet
	for (int i = 0; i < map.size(); i++) {
		visited.push_back(0);
	}
	//we traverse every node with all possible start points by calling dfs on every node i. 
	for (int i = 0; i < adjacencyMatrix.size(); i++) {
		std::cout << "start node: " << i + 1 << std::endl;
		dfs(i,adjacencyMatrix);
		//once dfs is complete, we should have been able to visit all nodes in G if graph is connected. is not, then one entry in visited will be false and hence the method
		//will return false;
		for (int i = 0; i < visited.size(); i++) {
			if (!visited[i]) {
				return false;
			}
		}
		//we set visited back to false and prepare for the next iteration over a different start point
		for (int i = 0; i < visited.size(); i++) {
			visited[i] = false;
		}

	}
	std::cout << std::endl;
	for (int i = 0; i < adjacencyMatrix.size();i++) {
		for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
			std::cout << adjacencyMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return true;
}
std::vector<std::vector<int>> Map::constructUnidirectionalMatrix() {
	std::vector<std::vector<int>> adjacencyMatrix;
	//i is the iterator over the map vector. it goes from 0 to the size of G
	for (int i = 0; i < size; i++) {
		std::vector<int> adjacencyMatrixRow;
		//std::cout << "in here";
		//j is the iterator over every row in the adjacencyMatrix. every row corresponds to a territory and its neighbours.if an entry has been assigned one, it 
		//means that the territory at row i has a neighbour at column j
		for (int j = 0; j < size; j++) {
			bool isNeighbour = false;
			if (i == j) {
				adjacencyMatrixRow.push_back(0);
			}
			else {
				if (map[i].size() > 1) {
					//z is the iterator over the columns of the map. we identify from this loop all neighbours of a territory i and assign 1 to an entry in [i][j]
					for (int z = 1; z < map[i].size(); z++) {
						int map_entry_index = map[i][z]->getTerritoryID() - 1;
						if (map_entry_index == j) {
							adjacencyMatrixRow.push_back(1);
							isNeighbour = true;
						}
					}
				}
				if (!isNeighbour) {
					adjacencyMatrixRow.push_back(0);
				}
			}
		}
		//once the row has been filled , we add it to the matrix
		adjacencyMatrix.push_back(adjacencyMatrixRow);
	}
	//the last loop takes care of the unidirectional change. for every entry 1 in [i][j] , we set 1 to the opposite entry [j][i]
	for (int i = 0; i < adjacencyMatrix.size();i++) {
		for (int j = 0; j < adjacencyMatrix[i].size();j++) {
			if (adjacencyMatrix[i][j] == 1 && adjacencyMatrix[j][i] == 0){
				adjacencyMatrix[j][i] = 1;
			}
			else if (adjacencyMatrix[i][j] == 0 && adjacencyMatrix[j][i] == 1) {
				adjacencyMatrix[i][j] = 1;
			}
		}
	}
	return adjacencyMatrix;
}
void Map::dfs(int start, std::vector<std::vector<int>> adjacencyMatrix) {
	//classic dfs algorithm. with a int matrix, things get simplified since we only push and pop integers.
	std::stack<int> stack;
	stack.push(start);
	visited[start] = true;
	while (!stack.empty()) {
		int id_index_visited = stack.top();
		stack.pop();
		std::cout << "visited = " << id_index_visited + 1 << std::endl;
		for (int i = 0; i < adjacencyMatrix[id_index_visited].size(); i++) {
			if (!visited[i]) {
				if (adjacencyMatrix[id_index_visited][i] == 1) {
					stack.push(i);
					visited[i] = true;
				}
			}
		}
	}
}