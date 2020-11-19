#include <iostream> // for displaying to console
#include "Part1GameEngine.h" //headerfile
#include"GameEngine.h";
#include"GameObservers.h";
void part_1::start() {

	cout << "//=======================================//\n";
	cout << "		Creating Map\n";
	cout << "//=======================================//\n";
	SelectMap* selectmap = new SelectMap("./MapFiles/");
	selectmap->printGameMaps();
	selectmap->setMap(); // choose swiss.map to check the case of invalid map // spain map is showing runtime exception
	selectmap->loadmap();
	Map* map = selectmap->map;
	GameEngine* engine = new GameEngine(map);
	PhaseObserver* phaseObserver = new PhaseObserver(engine);
	StatsObserver* statsObserver = new StatsObserver(engine);
	int phaseObserverOn = 0;
	int statsObserverOn = 0;
	cout << endl << "Pleaser enter 1 if you wish to turn on the observer" << endl;
	cin >> phaseObserverOn;
	if (phaseObserverOn == 1) { phaseObserver->TurnOn(); }
	cout << endl << "Pleaser enter 2 if you wish to turn on stats observer" << endl;
	cin >> statsObserverOn;
	if (statsObserverOn == 2) { statsObserver->TurnOn(); }

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


	cout << "//=======================================//\n";
	cout << "	Checking Deep Copy Constructor\n";
	cout << "//=======================================//\n";

	// ============For SelectMap=============//

	SelectMap* selectmap2 = new SelectMap(*selectmap);
	selectmap2->map = NULL;
	cout << *selectmap2;
	cout << *selectmap;

	// ===========For SelectPlayers===========//
	SelectPlayers* selectplayers2 = new SelectPlayers(*selectplayers);
	cout << *selectplayers2;
	cout << *selectplayers;
	cout << "\n\n";


	cout << "//=======================================//\n";
	cout << "   Checking Assignment Operator Overload\n";
	cout << "//=======================================//\n";

	// ============For SelectMap=============//

	SelectMap* selectmap3 = new SelectMap("C:/Users/pauru/Documents/Maps");
	selectmap3->printGameMaps();
	selectmap3->setMap(); // choose swiss.map to check the case of invalid map 
	selectmap3->loadmap();

	*selectmap3 = *selectmap;
	cout << *selectmap3;
	cout << *selectmap;

	// ============For SelectPlayers=============//

	SelectPlayers* selectplayers3 = new SelectPlayers();
	selectplayers3->setnumPlayers();
	selectplayers3->createPlayers();
	cout << "Adding cards to Deck\n";
	selectplayers3->createDeck();

	*selectplayers3 = *selectplayers;
	cout << *selectplayers3;
	cout << *selectplayers;
	cout << "\n\n";

	cout << "//=======================================//\n";
	cout << "		Checking Deconstruction\n";
	cout << "//=======================================//\n";

	// ============For SelectMap=============//

	delete(selectmap);
	delete(selectmap3);
	cout << "\n\n";

	// ============For SelectPlayers=============//

	delete(selectplayers);
	delete(selectplayers3);
}