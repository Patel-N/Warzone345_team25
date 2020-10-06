// Warzone_T25.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include"Map.h";
int main()
{
    //std::cout << "Hello World!\n";
	Map map("created map");
	map.addTerritory(1, "Brazil");
	map.addTerritory(2, "Canada");
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
	map.addTerritory(23, "Cuba");*/
	std::vector<int> border = { 1,2,4 };
	map.addBorder(border);
	border = { 2};
	map.addBorder(border);
	border = { 3 };
	map.addBorder(border);
	border = { 4,2};
    map.addBorder(border);
	map.printMap();
	/*border = { 5,4,6 };
	map.addBorder(border);
	border = { 6,3,5 };
	map.addBorder(border);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "map size: " << map.getSize();*/
	
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
