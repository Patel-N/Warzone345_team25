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

	virtual Map* generateMap(std::string fn);



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

class ConquestFileReader {

public:
	ConquestFileReader();

	~ConquestFileReader();

	ConquestFileReader(const ConquestFileReader &cml);

	void setFileName(string fn);

	virtual Map* generateMap(string fn);

	string getFileName();

private:
	string fileName;

	vector<string> splitLine(string line);

};

class ConquestFileReaderAdapter : public MapLoader{

public:
	Map* generateMap(string fn);

private:
	ConquestFileReader conquestFR;
};