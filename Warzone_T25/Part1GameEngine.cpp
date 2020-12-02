#include <iostream> // for displaying to console
#include <dirent.h> //for displaying the files in map directory // requires downloading direct.h and copying it in Studio include folder- as dirent.h is not included invisual studio but available in mingw
#include <fstream> //for opening and reading files
#include <vector> //contains players vector
#include "Part1GameEngine.h" ///headerfile


//================================================================================//
//								SelectMap									   	  //
//================================================================================//

// Constructor
SelectMap::SelectMap(string str, MapLoader* loader) {
	cout << "SelectMap Constructor Called\n";
	path = str;
	maploader = loader;
	//map = new Map("Map Creation Initialised");
	map = NULL;

	loaders[0] = new MapLoader();
	loaders[1] = new ConquestFileReaderAdapter(new ConquestFileReader());
}

SelectMap::SelectMap() {
	cout << "SelectMap Empty Constructor Called\n";
	maploader = new MapLoader();
	//map = new Map("Map Creation Initialised");
	map = NULL;
}

// traverse all files in the map directory and display to console all map files
void SelectMap::printGameMaps() {

	vector<string> allFileName;

	if (path.empty()) {
		cout << "Map directory path is not set: \n";
		return;
	}
	DIR* dp;
	dirent* pdir;
	char* ch_path = &path[0];
	dp = opendir("./MapFiles");
	cout << "Game directory has all these maps:" << "\n";
	if (dp) {
		while ((pdir = readdir(dp)) != NULL) {
			if (strcmp(pdir->d_name, ".") != 0 && strcmp(pdir->d_name, "..") != 0) {
				string s = pdir->d_name;
				if (s.substr(s.find_last_of(".") + 1) == ("map")) {
					string fName = "./MapFiles/" + s;
					allFileName.push_back(fName);
				}
			}
		}
	}
	DIR* dp2;
	dp2 = opendir("./MapFiles/ConquestFiles");
	if (dp2) {
		while ((pdir = readdir(dp2)) != NULL) {
			if (strcmp(pdir->d_name, ".") != 0 && strcmp(pdir->d_name, "..") != 0) {
				string s = pdir->d_name;
				if (s.substr(s.find_last_of(".") + 1) == ("map")) {
					string fName = "./MapFiles/ConquestFiles/" + s;
					allFileName.push_back(fName);
				}
			}
		}
	}
	closedir(dp);
	closedir(dp2);

	//Print all Files
	for (int i = 0; i < allFileName.size(); i++) {
		cout << allFileName[i].substr(allFileName[i].find_last_of("/") + 1) << endl;
	}
	
	setAllFiles(allFileName);
}

// take user inout to select the map file from directory and set to selectedmap (member variable)
void SelectMap::setMap() {
	string name;
	cout << "\nEnter the map name (with extension) that you wish to play:\n";
	cin >> name; //without spaces
	string filename = path + "/" + name;
	ifstream filehandle;
	filehandle.open(filename);

	while (!filehandle.is_open()) {
		cout << "You entered wrong file name. Try Again! Enter map name (with extension) that you wish to play:\n";
		cin >> name;
		filename = path + "/" + name;
		filehandle.open(filename);
	}
	filehandle.close();
	selectedmap = filename;
}

void SelectMap::setMapV2() {
	string name;
	cout << "\nEnter the map name (with extension) that you wish to play:\n";
	cin >> name; //without spaces
	
	string selectedPath;
	for (int i = 0; i < allFiles.size(); i++) {
		if (name == allFiles[i].substr(allFiles[i].find_last_of("/")+1)) {
			selectedPath = allFiles[i];
			break;
		}
	}

	ifstream filehandle;
	filehandle.open(selectedPath);

	while (!filehandle.is_open()) {
		cout << "You entered wrong file name. Try Again! Enter map name (with extension) that you wish to play:\n";
		cin >> name;

		for (int i = 0; i < allFiles.size(); i++) {
			if (name == allFiles[i].substr(allFiles[i].find_last_of("/") + 1)) {
				selectedPath = allFiles[i];
				break;
			}
		}

		filehandle.open(selectedPath);
	}
	filehandle.close();

	selectedmap = selectedPath;
}

// loadmap to map pointer until a validated map is selected by user
void SelectMap::loadmap() {

	//Determine which loader to use
	if (getSelectedMap().find("ConquestFiles") == string::npos) {
		setMapLoader(loaders[0]);
	}
	else {
		setMapLoader(loaders[1]);
	}

	while (map == NULL) {
		map = maploader->generateMap(getSelectedMap());
		if (map == NULL) {
			cout << "Map could not be validated and loaded. Please try different map. \n\n";
			printGameMaps();
			setMap();
		}
	}
}

// getter
string SelectMap::getSelectedMap() {
	return selectedmap;
}

// Deep Copy Constructor
SelectMap::SelectMap(const SelectMap& selectmap) {
	cout << "SelectMap Deep Copy Constructor called\n";
	path = selectmap.path;
	selectedmap = selectmap.selectedmap;
	map = new Map(*selectmap.map);
	maploader = new MapLoader(*selectmap.maploader);
}

// Destructor
SelectMap::~SelectMap() {
	cout << "SelectMap De-constructor called\n";
	if (map != NULL) {
		delete(map);
	}
	if (maploader != NULL) {
		delete(maploader);
	}
}

// Overload - insertion operator
ostream& operator << (ostream& output, const SelectMap& selectmapobj) {
	if (selectmapobj.selectedmap.empty()) {
		output << "==================================================================\n";
		output << "No map has been selected yet. Maps are stored at directory: " << selectmapobj.path << "\n";
		output << "==================================================================\n";
	}
	else {
		output << "==================================================================\n";
		output << "The selected map for this play is: " << selectmapobj.selectedmap << "\nAnd this map is stored at directory- " << selectmapobj.path << "\n";
		if (selectmapobj.map != NULL) {
			output << "This map has been successfully validated and loaded\n";
		}
		else {
			output << "This map couldn't be validated\n";
		}
		output << "==================================================================\n";
	}
	return output;
}

// Overload - assignment operator - deep copy
SelectMap& SelectMap::operator=(const SelectMap& selectmap) {
	cout << "SelectMap Assignment Operator Copy Constructor (deep copy) called\n";
	if (this == &selectmap) {
		return *this;
	}
	path = selectmap.path;
	selectedmap = selectmap.selectedmap;
	if (map != NULL) {
		delete(map); //ensuring no memory leak
		map = NULL;
	}
	if (maploader != NULL) {
		delete(maploader); //ensuring no memory leak
		maploader = NULL;
	}

	map = new Map(*selectmap.map);
	maploader = new MapLoader(*selectmap.maploader);
}


//================================================================================//
//								SelectPlayer 		   						   	  //
//================================================================================//


// constructor 
SelectPlayers::SelectPlayers() {
	cout << "SelectPlayers Constructor Called\n";
	numplayers = 0;
	deck = NULL;
}

// getter
int SelectPlayers::getnumPlayers() {
	return numplayers;
}

// asks user to provide number of players
void SelectPlayers::setnumPlayers() {
	int num = 0;
	cout << "Enter the number of players (2-5) that wish to play this game:\n";
	cin >> num;
	while (num < 2 || num > 5) {
		cout << "Please enter an integer between 2 (inclusive) and 5 (inclusive)\n";
		cin >> num;
	}
	numplayers = num;
}

// create players with names and place them in vector
void SelectPlayers::createPlayers() {
	string playername;
	int armystrength = 0;
	if (getnumPlayers() == 2) {
		armystrength = 40;
	}
	if (getnumPlayers() == 3) {
		armystrength = 35;
	}
	if (getnumPlayers() == 4) {
		armystrength = 30;
	}
	if (getnumPlayers() == 5) {
		armystrength = 25;
	}
	for (int i = 0; i < getnumPlayers(); i++) {
		cout << "Enter Player " << i << " name\n";
		cin >> playername;
		Player* player = new Player(i + 1, playername, armystrength); //army initial strength not known - to be discussed
		player->setPlayerHand(NULL);
		allPlayers.push_back(player);
	}
}

// create vector of cards and set deck pointer to it
void SelectPlayers::createDeck() {
	deck = new Deck();
	cout << "Inside- Part1 GameEngine: Adding cards to deck.\n" << endl;
	for (int i = 1; i <= 25; i++) {
		Card* card = new Card(rand() % 5 + 1);
		card->set_type(rand() % 5 + 1);
		deck->addCardToDeck(card);

		// Assignment operator
		if (i == 24) {
			Card* card3;
			card3 = card;

			// Insertion Stream Operator
			cout << "\nInsertion stream for card3 object: " << *card3 << endl;
			cout << "Assignment Operator: \ncard.type: " << card->get_type() << " Address: " << &card << endl;
			cout << "card3.type: " << card3->get_type() << " Address: " << &card3 << endl;
		}

		// Copy contructor
		if (i == 25) {
			Card* card2 = card;
			cout << "\nCopy Constructor: " << endl;
			cout << "card.type: " << card->get_type() << " Address: " << &card << endl;
			cout << "card2.type: " << card2->get_type() << " Address: " << &card2 << endl;

		}
	}
	cout << "\n25 cards were added to the deck.\n" << endl;
}


// Deep Copy Constructor
SelectPlayers::SelectPlayers(const SelectPlayers& selectplayer) {
	cout << "SelectPlayers deepcopy constructor called\n";
	numplayers = selectplayer.numplayers;
	for (int i = 0; i < selectplayer.allPlayers.size(); i++) {
		allPlayers.push_back(new Player(*selectplayer.allPlayers[i]));
	}
	deck = new Deck(*selectplayer.deck);
}

// Destructor
SelectPlayers::~SelectPlayers() {
	cout << "SelectPlayers De-constructor called\n";
	if (deck != NULL) {
		delete(deck);
	}
	for (unsigned int i = 0; i < allPlayers.size(); i++) {
		if (allPlayers[i] != NULL) {
			delete(allPlayers[i]);
		}
	}
	allPlayers.clear();
}

// Overload - insertion operator
ostream& operator << (ostream& output, const SelectPlayers& selectplayerobj) {
	if (selectplayerobj.numplayers <= 0) {
		output << "==================================================================\n";
		output << "No players have signed up for playing this game yet\n";
		output << "==================================================================\n";
	}
	else {
		output << "==================================================================\n";
		output << "Number of players playing this game are: " << selectplayerobj.numplayers << "\n";
		output << "Name of players playing this game are: \n";
		for (int i = 0; i < selectplayerobj.numplayers; i++) {
			output << "\t" << selectplayerobj.allPlayers[i]->getPlayerName() << "\n";
		}
		output << "==================================================================\n";
	}
	return output;
}

// Overload - assignment operator - deep copy
SelectPlayers& SelectPlayers::operator=(const SelectPlayers& selectplayer) {
	cout << "SelectPlayers Assignment Operator Copy Constructor (deep copy) called\n";
	if (this == &selectplayer) {
		return *this;
	}
	numplayers = selectplayer.numplayers;
	// to do- call destructor else memory leak for all players
	for (unsigned int i = 0; i < allPlayers.size(); i++) {
		if (allPlayers[i] != NULL) {
			delete(allPlayers[i]);
		}
	}
	allPlayers.clear();
	for (int i = 0; i < selectplayer.allPlayers.size(); i++) {
		allPlayers.push_back(new Player(*selectplayer.allPlayers[i]));
	}
	if (deck != NULL) {
		delete(deck);
	}
	deck = new Deck(*selectplayer.deck);
}

// Observer
//ChangeObserver::ChangeObserver() {
//	Observer* observer = new StatObserver;
//}
//	ChangeObserver();
//	void turnon(); //ob->changebserver();
//
//
//	void turnoff(); //ob->changebserver();
//	//friend ostream& operator<<(ostream& outs, const ChangeObserver& changeobserverobj);
//};