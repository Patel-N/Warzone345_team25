#include <iostream> 
#include "Part1GameEngine.h"
#include"GameEngine.h";
#include"GameObservers.h";

void part_1::start() {

	cout << "//=======================================//\n";
	cout << "		Creating Map\n";
	cout << "//=======================================//\n";

	SelectMap* selectmap = new SelectMap();

	selectmap->printGameMaps();
	selectmap->setMap(); // choose swiss.map to check the case of invalid map
	selectmap->loadmap();

	cout << *selectmap; // check insertion stream overload
	cout << "\n";

	cout << "//=======================================//\n";
	cout << "		Creating Players\n";
	cout << "//=======================================//\n";
	SelectPlayers* selectplayers = new SelectPlayers();
	selectplayers->setnumPlayers();
	selectplayers->createPlayers();
	cout << "\n\n";

	//=============Adding DecK===============//
	cout << "===========================\n";
	cout << " Adding cards to Deck\n";
	cout << "===========================\n";
	selectplayers->createDeck();
	cout << *selectplayers; // check insertion stream overload
	cout << "\n\n";
}