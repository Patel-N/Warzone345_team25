#pragma once
#include "Map.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class MapLoader
{

public:
	//ctors
	MapLoader();

	//Destructors
	~MapLoader();

	//Copy ctors
	MapLoader(const MapLoader &ml);

	//Setter
	void setFileName(std::string);

	//Getter
	std::string getFileName();

	//Insertion Operator
	friend ostream& operator<<(ostream& outs, const MapLoader& mapLoaderObject);

	//Assignment Operator
	MapLoader& operator= (const MapLoader& mlObj);

	Map generateMap(std::string fn);


private:	
	std::string fileName;

	//Helper method
	std::vector<std::string> splitLine(std::string line);
};


class IncorrectFileException {
};

class MissingElementException {
};

class DisconnectedMapException {
};

