// Warzone_T25.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include"Map.h";
int main()
{

	//Territory* t1_pt = new Territory(1, "Brazil", 1);
	//std::cout << *t1_pt;
	//std::cout << std::endl << std::endl;
	//Territory* t2_pt;
	//t2_pt = new Territory(2, "France", 2);
	/*std::cout << *t2_pt;
	std::cout << std::endl << std::endl;
	*t2_pt = *t1_pt;
	std::cout << *t2_pt;
	std::cout << std::endl << std::endl;
	std::cout << std::endl << std::endl;
	t2_pt->setTerritoryName("baloom");
	std::cout << *t1_pt;
	std::cout << std::endl << std::endl;
	//Territory* newTerritory2 = newTerritory;
	//t1 = t2;
	//std::cout << *newTerritory2;
	std::cout << std::endl << std::endl;
	//newTerritory2->setTerritoryName("Congo");
	//std::cout << *newTerritory2;
	std::cout << std::endl << std::endl;
	//std::cout << newTerritory;
	std::cout << std::endl << std::endl;*/

	

	
	/*Continent *continent = new Continent(1, "NA", 5);
	continent->addTerritoryToContinent(newTerritory);
	cout << *continent;*/
	/*Continent continent(1, "NA", 5);
	continent.addTerritoryToContinent(t1_pt);
	continent.addTerritoryToContinent(t2_pt);
	std::cout << continent;
	std::cout << std::endl << std::endl;
	Continent continentTwo = continent;
	std::cout << continentTwo;
	std::cout << std::endl << std::endl;
	continentTwo.getContinentTerritoryList()[0]->setTerritoryName("updated_Brazil");
	std::cout << "Here is the original continent after updating its copy: " << std::endl;
	std::cout << continent;
	std::cout << std::endl << std::endl;
	std::cout << "Here is the copy continent after updating: " << std::endl;
	std::cout << continentTwo;
	std::cout << std::endl << std::endl;*/
	
	/*Map map("created map");
	map.addContinent(1, "NA", 7);
	map.addContinent(2, "SA", 3);
	map.addContinent(3, "EU", 5);

	
    //std::cout << "Hello World!\n";
	map.addTerritory(1, "Brazil",2);
	map.addTerritory(2, "Cuba", 2);

	map.addTerritory(3, "france", 3);
	map.addTerritory(4, "UK", 3);
	std::cout << std::endl;
	//std::cout << map;
	map.addTerritory(5, "Canada", 1);
	map.addTerritory(6, "Alaska", 1);

	std::vector<int> border = { 1,2,5 };
	map.addBorder(border);
	border = { 2,6 };
	map.addBorder(border);
	border = { 3 };
	map.addBorder(border);
	border = { 4,3 };
	map.addBorder(border);
	border = { 5,1 };
	map.addBorder(border);
	border = { 6};
	map.addBorder(border);
	map.printMap();*/
/*
	map.printContinents();
	if (map.areContinentsConnected()) {
		std::cout << std::endl;
		std::cout << "continents are connected";
		std::cout << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "**continents are not connected**";
		std::cout << std::endl;
	}
	
	/*map.addTerritory(2, "Canada");
	map.addTerritory(3, "France");
	map.addTerritory(4, "Cuba");
	/*map.addTerritory(5, "Lebanon");
	map.addTerritory(6, "Japan");
	map.addTerritory(7, "Argentina");
	map.addTerritory(8, "unreachable");
	map.addTerritory(11, "Cuba");
	map.addTerritory(13, "Cuba");
	map.addTerritory(14, "Cuba");
	map.addTerritory(15, "Cuba");
	map.addTerritory(1, "Cuba");
	map.addTerritory(6, "Cuba");
	map.addTerritory(17, "Cuba");
	map.addTerritory(18, "Cuba");
	map.addTerritory(19, "Cuba");
	map.addTerritory(21, "Cuba");
	map.addTerritory(22, "Cuba");
	map.addTerritory(23, "Cuba");
	std::vector<int> border = { 1,2,4 };
	map.addBorder(border);
	border = { 2};
	map.addBorder(border);
	border = { 3 };
	map.addBorder(border);
	border = { 4,3};
    map.addBorder(border);
	map.printMap();
	/*border = { 5,4,6 };
	map.addBorder(border);
	border = { 6,3,5 };
	map.addBorder(border);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "map size: " << map.getSize();
	
	if (!map.isConnected()) {
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "The map is not connected. System will exit now";
		std::cout << std::endl;
		exit(0);
	}
	else {
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "the map is connected";
		std::cout << std::endl;
	}*/
	/*Map map("created map");
	map.addContinent(1, "NA", 7);
	map.addContinent(2, "SA", 3);
	map.addContinent(3, "EU", 5);
	map.addTerritory(1, "Brazil", 2);
	map.addTerritory(2, "Cuba", 2);
	map.addTerritory(3, "Canada", 1);
	map.addTerritory(4, "France", 3);
	std::cout << map;
	std::cout << std::endl;
	std::cout << std::endl;
	Map map2("created map 2");
	map2 = map;
	std::cout << map2;
	std::cout << std::endl;
	std::cout << std::endl;
	map2.getContinents()[0]->setContinentName("updated_NA");
	map2.getContinents()[0]->getContinentTerritoryList()[0]->setTerritoryName("Updated_Canada");
	Map map3 = map2;
	map3.getContinents()[0]->getContinentTerritoryList()[0]->setTerritoryName("Updated__Updated_Canada");
	std::cout << "the original map: " << endl;
	std::cout << map;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "the updated  map: " << endl;
	std::cout << map2;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "the updated  map from map2: " << endl;
	std::cout << map3;
	std::cout << std::endl;
	std::cout << std::endl;*/
	/*Map map("created map");
	map.addContinent(1, "NA", 7);
	map.addContinent(2, "SA", 3);
	map.addContinent(3, "EU", 5);

	map.addTerritory(1, "Canada", 1);

	map.addTerritory(2, "Brazil", 2);
	map.addTerritory(3, "Cuba", 2);
	map.addTerritory(4, "Mexico", 2);
	
	map.addTerritory(5, "France", 3);
	map.addTerritory(6, "Germany", 3);
	map.addTerritory(7, "England", 3);*/
	/*case where territories are connected but not continents*/
	Map map("created map");
	map.addContinent(1, "NA", 7);
	map.addContinent(2, "SA", 3);
	map.addContinent(3, "EU", 5);


	map.addTerritory(1, "Brazil", 2);
	map.addTerritory(2, "Cuba", 2);
	map.addTerritory(3, "Mexico", 2);

	map.addTerritory(4, "France", 3);
	map.addTerritory(5, "Germany", 3);
	map.addTerritory(6, "England", 3);
	map.addTerritory(7, "Canada", 1);
	std::vector<int> border = { 1,2,4 };
	map.addBorder(border);
	border = { 2,3 };
	map.addBorder(border);
	border = { 3 };
	map.addBorder(border);
	border = { 4};
	map.addBorder(border);
	border = {5};
	map.addBorder(border);
	border = { 6,3,5};
	map.addBorder(border);
	border = { 7,1};
	map.addBorder(border);
	cout << endl;
	map.printMap();
	if (map.validate()) {
		cout << ">>SUCCESS, THE MAP IS VALID";
	}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
