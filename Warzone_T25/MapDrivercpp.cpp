
#include <iostream>
#include"Map.h";
using namespace std;
void part_1::start() {
	Map* map = new Map("Created map");
		map->addContinent(1, "Skandinavien", 4);
		map->addContinent(2, "Westeuropa", 5);
		map->addContinent(3, "Mittelmeer", 3);
		map->addContinent(4, "Mitteleuropa", 4);
		/*ap.addContinent(5, "Balkan", 3);
		map.addContinent(6, "Kleinasien", 3);
		map.addContinent(7, "Russland", 7);*/

		map->addTerritory(1, "Reykjavik", 1);
		map->addTerritory(2, "Ostisland", 1);
		map->addTerritory(3, "Aberdeen", 2);

		map->addTerritory(4, "Glasgow", 2);
		map->addTerritory(5, "Nordirland", 2);
		map->addTerritory(6, "Dublin", 2);
		map->addTerritory(7, "Suedirland", 2);
		map->addTerritory(8, "Leeds", 2);
		map->addTerritory(9, "wales", 2);
		map->addTerritory(10, "England", 2);
		map->addTerritory(11, "London", 2);
		map->addTerritory(12, "Lisabon", 3);
		map->addTerritory(13, "Porto", 3);
		map->addTerritory(14, "Baskenl", 3);
		map->addTerritory(15, "Barcelona ", 4);
		map->addTerritory(16, "Madrid", 4);
		map->addTerritory(17, "Ballearen", 4);

		//std::cout << map;
		std::vector<int> border = { 1 };
		map->addBorder(border);
		border = { 2,1 };
		map->addBorder(border);
		border = { 3,7 };
		map->addBorder(border);
		border = { 4,3 };
		map->addBorder(border);
		border = { 5,6 };
		map->addBorder(border);
		border = { 6 };
		map->addBorder(border);
		border = { 7,2 };
		map->addBorder(border);
		border = { 8,4,9 };
		map->addBorder(border);
		border = { 9,5,13,10 };
		map->addBorder(border);
		border = { 10,6,11 };
		map->addBorder(border);
		border = { 12,13 };
		map->addBorder(border);
		border = { 13,14 };
		map->addBorder(border);
		border = { 14,9,10,11 };
		map->addBorder(border);
		border = { 15,7,17 };
		map->addBorder(border);
		border = { 16,8,13,15,17 };
		map->addBorder(border);
		map->printMap();
		if (map->validate()) {
			cout << ">>SUCCESS, THE MAP IS VALID";
		}
		cout << "STREAM INSERTION OPERATOR DEMO: " << endl;
		cout << map;
		std::cout << endl << endl;
		cout << "COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR DEMO: " << endl;
		Map* map2 = new Map("created map2");
		*map2 = *map;
		std::cout << "This is address of map ";
		std::cout << map << endl << endl;
		std::cout << "This is address of map2 ";
		std::cout << map2 << endl << endl;
		map2->getContinents()[0]->getContinentTerritoryList()[0]->setTerritoryName("**MAP UPDATE**");
		cout << *map;
		std::cout << endl << endl;
		cout << "---------------------------------" << endl;
		cout << "           UPDATED MAP:          " << endl;
		cout << "---------------------------------" << endl;
		std::cout << *map2 << endl << endl;
}
