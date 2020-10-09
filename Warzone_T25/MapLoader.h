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