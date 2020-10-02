// Warzone_T25.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include"Map.h";
int main()
{
    std::cout << "Hello World!\n";
	Map map("created map");
	map.addTerritory(1, "Brazil");
	map.addTerritory(2, "Canada");
	map.addTerritory(3, "France");
	map.addTerritory(4, "Cuba");
	std::vector<int> border = { 1,2,3 };
	map.addBorder(border);
	border = { 2,1,4 };
	map.addBorder(border);
	border = { 4,3 };
	map.addBorder(border);
	std::cout << std::endl;
	map.printMap();


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
