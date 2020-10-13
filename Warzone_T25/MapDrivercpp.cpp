
#include <iostream>
#include"Map.h";
using namespace std;
void part_1::start() {
	Map* map = new Map("Created map");
		map->addContinent(1, "Atlantic_Provinces", 3);
		map->addContinent(2, "Ontario_and_Quebec", 4);
		map->addContinent(3, "Western_Provinces-South", 3);
		map->addContinent(4, "Western_Provinces-North", 2);
		map->addContinent(5, "Nunavut", 3);
		map->addContinent(6, "Northwestern_Territories", 2);

		map->addTerritory(1, "New_Brunswick", 1);
		map->addTerritory(2, "Prince_Edward_Island", 1);
		map->addTerritory(3, "Nova_Scotia", 1);

		map->addTerritory(4, "N&L-Newfoundland", 1);
		map->addTerritory(5, "N&L-Labrador", 1);
		map->addTerritory(6, "Quebec-North", 2);
		map->addTerritory(7, "Quebec-Central ", 2);
		map->addTerritory(8, "Quebec-South", 2);
		map->addTerritory(9, "Ontario-South", 2);
		map->addTerritory(10, "Ontario-West", 2);
		map->addTerritory(11, "Ontario-North", 2);
		map->addTerritory(12, "Manitoba-South", 3);
		map->addTerritory(13, "Saskatchewan-South", 3);
		map->addTerritory(14, "Alberta-South", 3);
		map->addTerritory(15, "British_Columbia-South", 3);
		map->addTerritory(16, "BC-Vancouver_Island", 3);
		map->addTerritory(17, "British_Columbia-North", 4);

		map->addTerritory(18, "Alberta-North", 4);
		map->addTerritory(19, "Saskatchewan-North", 4);
		map->addTerritory(20, "Manitoba-North", 4);
		map->addTerritory(21, "Nunavut-Continental", 5);
		map->addTerritory(22, "NU-Southern_Islands", 5);
		map->addTerritory(23, "NU-Baffin_Island", 5);
		map->addTerritory(24, "NU-Victoria_Island-East", 5);
		map->addTerritory(25, "NU-Northern_Islands", 5);
		map->addTerritory(26, "NU-Ellesmere_Island", 5);
		map->addTerritory(27, "NT-Northern_Islands", 6);
		map->addTerritory(28, "NT-Banks_Island", 6);
		map->addTerritory(29, "NT-Victoria_Island-West", 6);
		map->addTerritory(30, "Northwest_Territories-Continental", 6);
		map->addTerritory(31, "Yukon_Territory", 6);


		//std::cout << map;
		std::vector<int> border = { 1,8,2,3 };
		map->addBorder(border);
		border = { 2,1,3 };
		map->addBorder(border);
		border = { 3,1,2,4 };
		map->addBorder(border);
		border = { 4,3,5,7 };
		map->addBorder(border);
		border = { 5,4,7,6 };
		map->addBorder(border);
		border = { 6,5,7,22,23 };
		map->addBorder(border);
		border = { 7,4,5,6,8,11 };
		map->addBorder(border);
		border = { 8,1,7,9};
		map->addBorder(border);
		border = { 9,8,11,10 };
		map->addBorder(border);
		border = { 10,9,11,12 };
		map->addBorder(border);
		border = { 11,7,9,10,20,22 };
		map->addBorder(border);
		border = { 12,10,13,20};
		map->addBorder(border);
		border = { 13,12,19,14 };
		map->addBorder(border);
		border = { 14,13,18,15};
		map->addBorder(border);
		border = { 15,14,16,17};
		map->addBorder(border);
		border = { 16,15};
		map->addBorder(border);
		border = { 17,15,31,30,18 };
		map->addBorder(border);
		border = { 18,14,17,19,30 };
		map->addBorder(border);
		border = { 19,13,18,20,30 };
		map->addBorder(border);
		border = { 20,11,12,19,30};
		map->addBorder(border);
		border = { 21,20,22,23,24,25,30};
		map->addBorder(border);
		border = { 22,6,11,21,23};
		map->addBorder(border);
		border = { 23,6,21,22,26,25 };
		map->addBorder(border);
		border = { 24,21,25,29};
		map->addBorder(border);
		border = { 25,21,23,24,26,27 };
		map->addBorder(border);
		border = { 26,23,25};
		map->addBorder(border);
		border = { 27,25,28,29 };
		map->addBorder(border);
		border = { 28,27,29,30 };
		map->addBorder(border);
		border = { 29,24,27,28,30};
		map->addBorder(border);
		border = { 30,17,18,19,21,28,29,31};
		map->addBorder(border);
		border = { 31,17,30};
		map->addBorder(border);
		map->printMap();
		if (map->validate()) {
			cout << ">>SUCCESS, THE MAP IS VALID";
		}
		cout << "STREAM INSERTION OPERATOR DEMO: " << endl;
		cout << *map;
		std::cout << endl << endl;
		cout << "COPY CONSTRUCTOR AND ASSIGNMENT OPERATOR DEMO: " << endl;
		Map* map2 = new Map("created map2");
		*map2 = *map;
		std::cout << "This is address of map ";
		std::cout << map << endl << endl;
		std::cout << "This is address of map2 ";
		std::cout << map2 << endl << endl;
		map2->getContinents()[0]->getContinentTerritoryList()[0]->setTerritoryName("**MAP UPDATE**");
		//cout << *map;
		std::cout << endl << endl;
		cout << "---------------------------------" << endl;
		cout << "           UPDATED MAP:          " << endl;
		cout << "---------------------------------" << endl;
		//std::cout << *map2 << endl << endl;
}
