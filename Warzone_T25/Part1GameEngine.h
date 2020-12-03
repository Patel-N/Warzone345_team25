#pragma once
#include <iostream> // contains insertion operator overload
#include <vector> //contains players vector
#include"Player.h" // selectplayer has player pointer
#include"MapLoader.h" // Selectmap has maploader pointer
#include"Map.h" // selectmap has map pointer
//#include"Observer.h" 
using namespace std;


// methods to display map directory, open map, validate and load file
class SelectMap {

private:

	string path; // directory path
	string selectedmap; // userinput of map file
	Map* map; // points to generated map after validation, null if not validated
	MapLoader* maploader; // points to maploader object to access generatemap method with arguments of selectedmap
	MapLoader* loaders[2];
	vector<string> allFiles;

public:

	// Empty Constructor
	SelectMap();

	// traverse all files in the map directory and display to console all map files
	void printGameMaps();

	// take user inout to select the map file from directory and set to selectedmap (member variable)
	void setMap();

	// loadmap to map pointer until a validated map is selected by user
	void loadmap();

	// getter
	string getSelectedMap();
	inline Map* getMap() { return map; };

	//Setter
	inline void setAllFiles(vector<string> s) { allFiles = s; };
	inline void setMapLoader(MapLoader* ml) { maploader = ml; };

	// Deep Copy Constructor
	SelectMap(const SelectMap& selectmap);

	// Destructor
	~SelectMap();

	// Overload - insertion operator
	friend ostream& operator << (ostream& outs, const SelectMap& selectmap);

	// Overload - assignment operator - deep copy
	SelectMap& operator=(const SelectMap& selectmap);

};

// generate players
class SelectPlayers {

public:

	int numplayers; // to store user input of number of players
	vector <Player*> allPlayers; // generated players are stored in this vector
	Deck* deck; // deck pointer to point to deck of cards


public:

	// constructor 
	SelectPlayers();

	// getter
	int getnumPlayers();

	// ask user to provide number of players
	void setnumPlayers();

	// create players with names and place them in vector
	void createPlayers();

	// create vector of cards and set deck pointer to it
	void createDeck();

	// Deep Copy Constructor
	SelectPlayers(const SelectPlayers& selectplayer);

	// Destructor
	~SelectPlayers();

	// Overload - insertion operator
	friend ostream& operator << (ostream& output, const SelectPlayers& selectplayers);

	// Overload - assignment operator - deep copy
	SelectPlayers& operator=(const SelectPlayers& selectplayer);

};

namespace part_1 {
	void start();
}