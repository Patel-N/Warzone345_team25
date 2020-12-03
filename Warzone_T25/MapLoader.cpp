#include "MapLoader.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <exception>



//Ctors
MapLoader::MapLoader() {
	cout << "Map Loader initialized" << endl;
}

MapLoader::~MapLoader()
{
	cout << "MapLoader destroyed." << endl;
}

//Copy ctor
MapLoader::MapLoader(const MapLoader& ml) {
	setFileName(ml.fileName);
}

//Getters & Setters
std::string MapLoader::getFileName() {
	return fileName;
}

void MapLoader::setFileName(std::string fn) {
	fileName = fn;
}

//Assignment Operator Overload
MapLoader& MapLoader::operator=(const MapLoader& mlObj)
{
	if (this != &mlObj) {
		fileName = mlObj.fileName;
	}

	return *this;
}

//Insertion Operator overload
ostream& operator<<(ostream& outs, const MapLoader& mapLoaderObject)
{
	if (mapLoaderObject.fileName.empty()) {
		outs << "Map hasn't been selected yet.";
	}
	else {
		std::string fileNameExtension = mapLoaderObject.fileName.substr(mapLoaderObject.fileName.find_last_of("/") + 1);
		outs << "Loaded map is: " << fileNameExtension.substr(0, fileNameExtension.find_last_of(".")) << endl;
	}

	return outs;
}

ostream& operator<<(ostream& outs, const ConquestTerritoriesHolder& obj)
{
	outs << "Id: " << "Name: " << "Continent: " << "BorderCount: " << endl;

	return outs;
}

/*
*
* Responsible of parsing the map when all elements of a map are found.
*
*/
Map* MapLoader::generateMap(string fn)
{
	Map* gameMap;
	//Map gameMap("Map initialized\n");
	gameMap = new Map("Map initialized\n");
	bool continentCheck = false;
	bool territoriesCheck = false;
	bool bordersCheck = false;

	Player* p = new Player();

	try {

		//File extension check
		if (fn.substr(fn.find_last_of(".") + 1) != ("map")) {
			throw IncorrectFileException();
		}

		setFileName(fn);


		ifstream mapFile(getFileName()); //Automatically opens the file
		if (mapFile.is_open()) {
			string line;

			//Populate continents
			int continentId = 1;
			while (getline(mapFile, line)) {

				//Marks beginning of continent info
				if (line == "[continents]") {
					getline(mapFile, line);
					continentCheck = true;
				}

				if (continentCheck) {
					//Marks end of continent info
					if (line == "") {
						break;
					}
					else {
						std::vector<string> sepInfo = splitLine(line);

						//Create new continents and add them to the Map
						gameMap->addContinent(continentId, sepInfo[0], stoi(sepInfo[1]));
						continentId++;
					}

				}
			}

			//Populate territories
			while (getline(mapFile, line)) {

				if (line == "[countries]") {
					getline(mapFile, line);
					territoriesCheck = true;
				}

				if (territoriesCheck) {
					//Marks end of territories info
					if (line == "") {
						break;
					}
					else {
						std::vector<string> sepInfo = splitLine(line);

						//Create new territories and add them to the Map
						gameMap->addTerritory(stoi(sepInfo[0]), sepInfo[1], stoi(sepInfo[2]));
					}

				}
			}

			//Populate borders
			while (getline(mapFile, line)) {

				if (line == "[borders]") {
					getline(mapFile, line);
					bordersCheck = true;
				}

				if (bordersCheck) {
					//Marks end of borders info
					if (line == "") {
						break;
					}
					else {
						std::vector<string> sepInfo = splitLine(line);
						std::vector<int> borders;

						//Convert strings to ints
						for (int i = 0; i < sepInfo.size(); i++) {
							borders.push_back(stoi(sepInfo[i]));
						}

						//Add borders to map
						gameMap->addBorder(borders);
					}

				}
			}

			mapFile.close();
		}
		else {
			throw FileNotFoundException();
		}

		//Throw an error if missing any info/wrong file structure
		if (!continentCheck || !territoriesCheck || !bordersCheck) {
			throw MissingElementException();
		}
		//Throw error if map is disconnected
		if (!gameMap->validate()) {
			throw DisconnectedMapException();
		}
		else {
			cout << "Map successfully generated!" << endl;
		}

	}
	catch (IncorrectFileException ife) {
		cout << "\n\nERROR: Incorrect file type.Please select a .map file." << endl << endl;
		return NULL;
	}
	catch (MissingElementException mee) {
		cout << "ERROR: One of the required set of information was not found." << endl << endl;
		return NULL;
	}
	catch (DisconnectedMapException dme) {
		cout << "ERROR: The map has disconnected territories or continent." << endl << endl;
		return NULL;
	}

	return gameMap;
}

/*
Helper class to split a string by a whitespace delimiter
*/
std::vector<std::string> MapLoader::splitLine(std::string line)
{
	std::regex reg("\\s");

	std::vector<std::string> splitLine(
		std::sregex_token_iterator(line.begin(), line.end(), reg, -1),
		std::sregex_token_iterator()
	);

	return splitLine;
}



ConquestFileReader::ConquestFileReader()
{
	cout << "Conquest Map Loader initialized\n";
}

ConquestFileReader::~ConquestFileReader()
{
	cout << "Deleting conquest file reader" << endl;
}

ConquestFileReader::ConquestFileReader(const ConquestFileReader& cml)
{
}

void ConquestFileReader::setFileName(string fn)
{
	fileName = fn;
}


bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

Map* ConquestFileReader::generateMap(string fn)
{
	Map* gameMap;
	//Map gameMap("Map initialized\n");
	gameMap = new Map("Map initialized\n");
	bool continentSection = false;
	bool territoriesSection = false;
	bool continentParsed = false;
	bool territoriesParsed = false;
	vector<ConquestTerritoriesHolder*> conquestTerritories;

	try {

		//File extension check
		if (fn.substr(fn.find_last_of(".") + 1) != ("map")) {
			throw IncorrectFileException();
		}

		setFileName(fn);

		ifstream mapFile(getFileName()); //Automatically opens the file
		if (mapFile.is_open()) {
			string line;

			//Populate continents
			int continentId = 1;
			int territoryId = 1;
			while (getline(mapFile, line)) {

				//SKIP NEWLINES
				if (!line.empty()) {
					//Beginning of continent section
					if (line == "[Continents]") {
						getline(mapFile, line);
						continentSection = true;
					}

					if (continentSection) {

						//Check if we get to territories section 
						if (line == "[Territories]") {
							continentParsed = true;

							continentSection = false;
							territoriesSection = true;
						}
						else {
							vector<string> sepInfo = splitLine(line, true);
							if (sepInfo.size() == 2) {
								//Create new continents and add them to the Map
								gameMap->addContinent(continentId, sepInfo[0], stoi(sepInfo[1]));
								continentId++;
							}
						}

					}

					//Territories section
					if (territoriesSection) {

						//Skip [Territories] line
						if (line != "[Territories]") {

							if (mapFile.eof() && line.empty()) {
								territoriesParsed = true;
							}
							else {
								vector<string> sepInfo = splitLine(line, false);
								vector<string> borders;

								//Build borders vector
								for (int i = 4; i < sepInfo.size(); i++) {
									borders.push_back(sepInfo[i]);
								}

								ConquestTerritoriesHolder* cth = new ConquestTerritoriesHolder(territoryId, sepInfo[0], sepInfo[3], borders);
								conquestTerritories.push_back(cth);

								territoryId++;

								//Determine if its number or name for continent
								vector<Continent*> conts = gameMap->getContinents();
								int cId = -1;

								for (int i = 0; i < conts.size(); i++) {
									if (cth->getContinent() == conts[i]->getContinentName()) {
										cId = conts[i]->getContinentID();
										break;
									}
								}


								gameMap->addTerritory(cth->getId(), cth->getName(), cId);

								//Set territories parsed flag to true
								if (mapFile.eof()) {
									territoriesParsed = true;
								}
							}
						}

					}

				}
			}

			//Build borders
			for (int i = 0; i < conquestTerritories.size(); i++) {
				vector<int> borders;
				borders.push_back(conquestTerritories[i]->getId());
				vector<string> cTerritoryBorders = conquestTerritories[i]->getBorders();
				for (int j = 0; j < cTerritoryBorders.size(); j++) {

					if (is_number(cTerritoryBorders[j])) {
						borders.push_back(stoi(cTerritoryBorders[j]));
					}
					else {
						Territory* bTerri = gameMap->getTerritory(cTerritoryBorders[j]);
						borders.push_back(bTerri->getTerritoryID());
					}
				}

				gameMap->addBorder(borders);
			}

			mapFile.close();
		}
		else {
			throw FileNotFoundException();
		}

		//Throw an error if missing any info/wrong file structure
		if (!continentParsed) {
			throw MissingElementException();
		}
		//Throw error if map is disconnected
		if (!gameMap->validate()) {
			throw DisconnectedMapException();
		}
		else {
			cout << "Map successfully generated!" << endl;
		}

	}
	catch (FileNotFoundException fnf) {
		cout << "ERROR: File was not found." << endl << endl;
		return nullptr;
	}
	catch (IncorrectFileException ife) {
		cout << "\n\nERROR: Incorrect file type.Please select a .map file." << endl << endl;
		return nullptr;
	}
	catch (MissingElementException mee) {
		cout << "ERROR: One of the required set of information was not found." << endl << endl;
		return nullptr;
	}
	catch (DisconnectedMapException dme) {
		cout << "ERROR: The map has disconnected territories or continent." << endl << endl;
		return nullptr;
	}
}

string ConquestFileReader::getFileName()
{
	return fileName;
}

vector<string> ConquestFileReader::splitLine(string line, bool isEqualSeparator)
{
	if (isEqualSeparator) {
		regex reg("=");

		vector<string> splitLine(
			sregex_token_iterator(line.begin(), line.end(), reg, -1),
			sregex_token_iterator()
		);

		return splitLine;
	}
	else {
		regex reg(",");

		vector<string> splitLine(
			sregex_token_iterator(line.begin(), line.end(), reg, -1),
			sregex_token_iterator()
		);

		return splitLine;
	}
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader* cFR) {
	conquestFR = cFR;
}

Map* ConquestFileReaderAdapter::generateMap(string fn)
{
	return conquestFR->generateMap(fn);
}

ConquestFileReaderAdapter::ConquestFileReaderAdapter(const ConquestFileReaderAdapter& conquestfilereaderadapter) {
	cout << "ConquestFileReaderAdapter Deep Copy Constructor called\n";
	conquestFR = new ConquestFileReader(*conquestfilereaderadapter.conquestFR);
}


ConquestFileReaderAdapter::~ConquestFileReaderAdapter() {
	delete conquestFR;
}

ConquestFileReaderAdapter& ConquestFileReaderAdapter:: operator= (const ConquestFileReaderAdapter& cFRA) {
	if (this != &cFRA) {
		return *this;
	}
	cout << "ConquestFileReaderAdapter Assignment Operload Overload called\n";
	delete conquestFR;
	conquestFR = new ConquestFileReader(*cFRA.conquestFR);
	return *this;
}

ConquestTerritoriesHolder::ConquestTerritoriesHolder()
{
}

ConquestTerritoriesHolder::ConquestTerritoriesHolder(int i, string n, string c, vector<string> b) : id(i), name(n), continent(c), borders(b)
{
}

ConquestTerritoriesHolder::~ConquestTerritoriesHolder()
{
}