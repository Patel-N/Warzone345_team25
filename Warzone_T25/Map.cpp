#include "Map.h";
#include "Player.h"
#include "string";
#include<iostream>;
#include<stack>;

Territory::Territory(int id, std::string newName, int continentID) : territoryId(id), territoryName(newName), territory_continentID(continentID){
	player = new Player();
	numArmies = 0;
}

Territory::Territory(const Territory& territory) {
	*this = territory;
}

Territory::Territory() {
	territoryId = 1;
	territoryName = "random";
	territory_continentID = 0;
	numArmies = 0;
}

Territory::~Territory() {
	
}

std::string Territory::getName() {
	return territoryName;
}

int Territory::getTerritoryID() {
	return territoryId;
}

int Territory::getTerritoryContinentID() {
	return territory_continentID;
}

void Territory::setTerritoryName(std::string newName) {
	territoryName = newName;
}

ostream& operator<<(ostream& outs, const Territory& theObject) {
	outs << "Territory name: " << theObject.territoryName << endl
		<< "Territory ID: " << theObject.territoryId << endl
		<< "Territory belongs to continent ID # " << theObject.territory_continentID << endl
		<< "Territory belongs to player # " << theObject.player<< endl
		<< "# of armies " << theObject.numArmies << endl;

		return outs;
	
}

Territory& Territory::operator=(const Territory& territory) {
	if (this != &territory) {
		territoryId = territory.territoryId;
		territoryName = territory.territoryName;
		territory_continentID = territory.territory_continentID;
		numArmies = territory.numArmies;
		Player* tempPlayer = new Player;
		player = tempPlayer;
		
	}
	return *this;
}

Continent::Continent(int id, std::string name, int bonus) : continentId(id), continentName(name), bonus(bonus) {
	//left empty on purpose to demonstrate fancy constructor syntax =)
}

Continent::Continent(const Continent& continent) {
	*this = continent;
}

Continent::~Continent() {
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

void Continent::setContinentName(std::string newName) {
	continentName = newName;
}

ostream& operator<<(ostream& outs, const Continent& theObject) {
	outs << "Continent name: " << theObject.continentName << endl
		<< "Continent ID: " << theObject.continentId << endl
		<< "Continent Bonus: " << theObject.bonus << endl
		<< "Continent territories:" << endl;
	for (auto x : theObject.continentTerritoryList) {
		outs << *x << endl;
	}
	outs << endl << endl;
		 
	return outs;

}

Continent& Continent::operator=(const Continent& continent) {
	if (this != &continent) {
		bonus = continent.bonus;
		continentName = continent.continentName;
		continentId = continent.continentId;
	}
	return *this;
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
	std::cout << message << endl;
}
Map::Map(const Map& map) {
	cout << "**** IN COPY CONSTRUCTOR*****" << endl;
	if (this != &map) {
		*this = map; 
	}
}

Map::~Map() {
	for (int i = map.size() - 1; i > 0; i--) {
		delete map[i][0];
		map[i].clear();
	}
	for (int i = 0; i < continents.size(); i++) {
		delete continents[i];
		continents[i] = NULL;
	}	
}

std::vector<Continent*> Map::getContinents() {
	return continents;
}

Map& Map::operator=(const Map& originalMap) {
	cout << "****IN ASSIGNMENT OPERATOR*****" << endl;
	for (int i = 0; i < originalMap.continents.size(); i++) {
		Continent* continent = new Continent(*originalMap.continents[i]);
		continents.push_back(continent);	
	}
	for (int j = 0; j < originalMap.map.size(); j++) {
		std::vector<Territory*> tempVector;
		Territory* territory = new Territory(*originalMap.map[j][0]);
		tempVector.push_back(territory);
		continents[territory->getTerritoryContinentID() - 1]->addTerritoryToContinent(territory);
		map.push_back(tempVector);
	}
	for (int i = 0; i < originalMap.map.size(); i++) {
		std::vector<int> borders;
		if (originalMap.map[i].size() > 1) {			
			for (int j = 1; j < originalMap.map[i].size(); j++) {
				borders.push_back(originalMap.map[i][j]->getTerritoryID());
			}
			if (borders.size() > 0) {				
				for (int z = 0; z < borders.size(); z++) {
					this->map[i].push_back(this->map[borders[z] - 1][0]);
				}
			}
		}
	}	
	return *this;
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

ostream& operator<<(ostream& outs, const Map& theObject) {
	outs << "----------------------------------" << endl
		<< "             MAP                  " << endl
		<< "----------------------------------" << endl << endl;
	outs << "----------------------------------" << endl
		<< "             CONTINENTS            " << endl
		<< "----------------------------------" << endl << endl;
	for (auto x : theObject.continents) {
		outs << *x << endl;
	}
	outs << endl;
	outs << "----------------------------------" << endl
		<< "             TERRITORIES           " << endl
		<< "----------------------------------" << endl << endl;
	for (auto x : theObject.map) {
		cout << *x[0] << endl;
	}
	return outs;
}

std::vector<Territory*> Continent::getContinentTerritoryList() {
	return continentTerritoryList;
}

/*The addTerritory method will not only add a territory but also insert it such that
the map vector remains sorted in increasing order*/
void Map::addTerritory(int id, std::string name,int continentID) {
	Territory* newTerritory = new Territory(id, name,continentID);
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
			std::cout << temp.getTerritoryID()<<"->";
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
	std::cout << "start node: " << 0<< std::endl;
	dfs(0,adjacencyMatrix);
	//once dfs is complete, we should have been able to visit all nodes in G if graph is connected. is not, then one entry in visited will be false and hence the method
	//will return false;
	//we set visited back to false and prepare for the next iteration over a different start point
	for (int i = 0; i < visited.size(); i++) {
		if (visited[i] == false) {
			return false;
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

bool Map::areContinentsConnected() {
	std::vector<std::vector<int>> adjacencyMatrix = constructUnidirectionalMatrix();
	for (int i = 0; i < continents.size(); i++) {
		
		continentsVisited.push_back(0);
	}
	for (int k = 0; k < continents.size(); k++) {
		std::cout << "start node: " << k;
		std::cout << endl;
		continentDfs(k,adjacencyMatrix);
		for (int j = 0; j < continentsVisited.size(); j++) {
			if (!continentsVisited[j]) {
				return false;
			}
		}
		for (int z = 0; z < continentsVisited.size(); z++) {
			continentsVisited[z] = 0;
		}
	}
	return true;
}

bool Map::uniqueTerritory() {

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			int number_of_reps = 0;
			int canditateID = map[i][j]->getTerritoryID();
			std::string candidateName = map[i][j]->getName();
			for (int k = 0; k < continents.size(); k++) {
				for (int z = 0; z < continents[k]->getContinentTerritoryList().size(); z++) {
					if (z == i) { continue; }
					else {
						if (canditateID == continents[k]->getContinentTerritoryList()[z]->getTerritoryID()) {
							number_of_reps++;
						}
					}
				}
			}
			if (number_of_reps > 1) { return false; }//a unique territory cannot repeat more than one time
		}
	}
	return true;
}

void Map::continentDfs(int start, std::vector<std::vector<int>> adjacencyMatrix) {	
	std::stack<int> stack;
	int continentID = continents[start]->getContinentID();
	stack.push(continentID);
	continentsVisited[start] = true;
	while (!stack.empty()) {	
		int continentIndexInStack = stack.top() - 1;	
		stack.pop();
		std::cout << "visited: " << continentIndexInStack << endl;
		std::vector<Territory*> territoriesInContinent = continents[continentIndexInStack]->getContinentTerritoryList();
		for (int i = 0; i < territoriesInContinent.size(); i++) {			
			int territoryID = territoriesInContinent[i]->getTerritoryID();
			int territoryIndex = territoryID - 1;//we are looking at the neighbours of that index
			std::vector<int> territoryNeighbours = adjacencyMatrix[territoryIndex]; //here we get the unidirectional neighbours of the territory of continent[i]
			for (int j = 0; j < territoryNeighbours.size(); j++) {
				if (j == territoryIndex) { continue; }//we are continuing if the index in question is the same as the territory since a territory
				//cannot be a neighbour of itself
				else {
					if (territoryNeighbours[j] == 1) {
						Territory* adjacentTerritory = map[j][0];
						int continentIndex = (*adjacentTerritory).getTerritoryContinentID() - 1;
						if (!continentsVisited[continentIndex]) {
							stack.push((*adjacentTerritory).getTerritoryContinentID());
							continentsVisited[continentIndex] = true;
						}
					}
				}
			}
		}
	}
}

bool Map::validate() {
	cout << "--------------Welcome to Validate--------------------" << endl;
	cout << ">>step 1: calling is Territory unique verrification..." << endl;
	bool isUnique = uniqueTerritory();
	if (isUnique) {
		cout << ">>step 1 complete: Territory is unique." << endl;
	}
	else {
		cout << ">>Step 1 FAILED: Territory not unique. There exits a duplicate";
	}
	std::cout << endl;
	cout << ">>step 2: calling isConnected to verify if map is a connected graph" << endl;
	bool is_connected = isConnected();
	if (is_connected) {
		cout << ">>step 2 SUCCESS: The entire map is connected." << endl;
	}
	else {
		cout << ">>Step 2 FAILED: The map is not connected ";
	}
	cout << ">>step 3: calling areContinentsConnected to verify if continents are a connected subgraphs" << endl;
	bool are_continents_connected = areContinentsConnected();
	std::cout << endl;	
	if (are_continents_connected) {
		cout << ">>step 3 SUCCESS: Continents are also connected" << endl;
	}
	else {
		cout << ">>Step 3 FAILED: The continents are not connected";
	}
	if (isUnique && is_connected && are_continents_connected) {
		return true;
	}
	else {
		return false;
	}
}
