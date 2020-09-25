#include "MapLoader.h"
#include <iostream>

void MapLoader::readFile(std::string fileName)
{
	cout << "Yerrr :D" << endl;

	ifstream mapFile("./MapFiles/canada.map"); //Automatically opens the file
	if (mapFile.is_open()) {
		string line;
		while (getline(mapFile, line))
		{
			cout << line << endl;
		}
		mapFile.close();
	}
	else {
		cout << "Couldn't read file." << endl;
	}

}