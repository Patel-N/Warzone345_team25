#pragma once
#include "GameObservers.h"
#include "GameEngine.h"
#include <Windows.h>
#include <iostream>

// OBSERVER CLASS

// Observer Default Constructor
Observer::Observer() {
}

// Observer Destructor
Observer::~Observer() {
}

// SUBJECT CLASS

// Subject Defalt Constructor creates lists for both Observers.
Subject::Subject() {
	phase_observers = new list<Observer*>;
	stats_observers = new list<Observer*>;

}

// Subject Destructor deletes both lists of observers.
Subject::~Subject() {
	delete phase_observers;
	delete stats_observers;

}
// Subject Constructor. If b is true then phase observer is calling the attach function.
void Subject::Attach(bool phase, Observer* o) {
	if (phase == true) {
		phase_observers->push_back(o);
	}
	else {
		stats_observers->push_back(o);
	}
};

// Removes the observer from its list.
void Subject::Detach(bool phase, Observer* o) {
	if (phase == true) {
		phase_observers->remove(o);
	}
	else {
		stats_observers->remove(o);
	}

};

// Iterates over list of observers and call update for each one.
void Subject::Notify(bool phase) {
	if (phase == true) {
		list<Observer*>::iterator it = phase_observers->begin();
		for (auto i = phase_observers->begin(); i != phase_observers->end(); ++i) {
			(*i)->Update();
		}
	}
	else {
		list<Observer*>::iterator it = stats_observers->begin();
		for (auto i = stats_observers->begin(); i != stats_observers->end(); ++i) {
			(*i)->Update();
		}
	}
};
// CHECK IF THIS IS RIGHT
// Copy Constructor- deep copy
Subject::Subject(const Subject& s) {
	cout << "Copy Constructor (deep copy): " << endl;
	for (int i = 0; s.phase_observers; i++) {
		this->phase_observers[i] = s.phase_observers[i];
	}

	for (int i = 0; s.stats_observers; i++) {
		this->stats_observers[i] = s.stats_observers[i];
	}

	}

// CHECK IF THIS IS RIGHT
// Overloaded Assignment Operator- deep copy
Subject& Subject::operator=(const Subject& s) {
	for (Observer* observer : *phase_observers) {
		delete observer;
	}

	for (Observer* observer : *stats_observers) {
		delete observer;
	}
	return *this;
}

// CHECK IF THIS IS RIGHT
// Insertion Stream Operator
ostream& operator<<(ostream& outs, const Subject& obj) {

return outs << "Subject stream insertion operaotr has been called." << endl;

}

// PHASE OBSERVER CLASS

// Phase Observer Default Constructor
PhaseObserver::PhaseObserver() {
};

// Constructor sets argument to this GameEngine object.
PhaseObserver::PhaseObserver(GameEngine* s) {
	
	_subject = s;

};

// Destructor removes observer from list.
PhaseObserver::~PhaseObserver() {
	_subject->Detach(true,this);
};

// CHECK IF THIS IS RIGHT
// Copy Constructor- deep copy
PhaseObserver::PhaseObserver(const PhaseObserver& s) {
	this->_subject = s._subject;

}

// CHECK IF THIS IS RIGHT
// Overloaded Assignment Operator- deep copy
PhaseObserver& PhaseObserver::operator=(const PhaseObserver& s) {
	this->_subject = s._subject;

	return *this;
}

// CHECK IF THIS IS RIGHT
// Insertion Stream Operator
ostream& operator<<(ostream& outs, const PhaseObserver& obj) {

	return outs << "Phase Observer stream insertion operaotr has been called." << endl;

}

// Calls the display function.
void PhaseObserver::Update() {
	//Called by Notify() when state of Subject changes

	display();
};

// Adds phase observer object to list.
void PhaseObserver::TurnOn() {
	_subject->Attach(true, this);
};

// Removes phase observer object to list.
void PhaseObserver::TurnOff() {
	_subject->Detach(true, this);
};

// Displays phase observer information for each game phase. 
void PhaseObserver::display() {
	int id = _subject->getPhase();
	string name = _subject->getPName();
	vector<Player*> players = _subject->getPlayers();

	// Displays info of phase depending on the phase ID. Using window library to use sleep method and delay output.
	switch(id) {
		case 0:
			/*Sleep(1500);
			system("cls");*/

			cout << "STARTUP PHASE\n" << endl;
			for (int i = 0; i < players.size(); i++) {
				name = players.at(i)->getPlayerName();

				// Displays player, their reinforcement pool and their territories.
				cout << name << " owns: " << endl;
				cout << "  reinforcement pool: " << players.at(i)->getArmyToBePlaced() << endl;
				for (int j = 0; j < players.at(i)->getPlayerTerritories().size(); j++) {
					cout << "  " <<players.at(i)->getPlayerTerritories().at(j)->getName() << endl;
				}
				cout << endl;
			}
			break;

		case 1:
		/*	Sleep(1500);
			system("cls");*/

			cout << name << ": " << "REINFORCEMENT PHASE\n" << endl;
			break;

		case 2:
	/*		Sleep(1500);
			system("cls");*/

			cout << name << ": " << "ISSUE ORDERS PHASE\n" << endl;
			break;

		case 3:
		/*	Sleep(1500);
			system("cls");*/

			// Loops the number of payers and displays the player and their order being executed.
			cout << name << ": " << "EXECUTION ORDERS PHASE\n" << endl;
			for (int i = 0; i < players.size(); i++) {
				// WAIT FOR ISSUE ORDERS BEFORE UNCOMMENTING
				if(players[i]->getOrderList()->numSize != 0 ) {
					cout << players[i]->getPlayerName() << " executes " << players[i]->getNextOrder()->getorderName() << endl << endl;
				}
			}
			
			break;

	}
};

// STATS OBSERVER CLASS

// StatsObserver Default Constructor
StatsObserver::StatsObserver() {
};

// StatsObserver Constructor assigns argument to this GameEngine Object.
StatsObserver::StatsObserver(GameEngine* s) {

	_subject = s;
};

// StatsObserver Destructor removes observer from list.
StatsObserver::~StatsObserver() {

	_subject->Detach(false,this);
};

// CHECK IF THIS IS RIGHT
// Copy Constructor- deep copy
StatsObserver::StatsObserver(const StatsObserver& s) {
	this->_subject = s._subject;

}

// CHECK IF THIS IS RIGHT
// Overloaded Assignment Operator- deep copy
StatsObserver& StatsObserver::operator=(const StatsObserver& s) {
	this->_subject = s._subject;

	return *this;
}

// CHECK IF THIS IS RIGHT
// Insertion Stream Operator
ostream& operator<<(ostream& outs, const StatsObserver& obj) {

	return outs << "Stats Observer stream insertion operaotr has been called." << endl;

}

// Calls display function.
void StatsObserver::Update() {
	display();
};

// Adds objects to stats observer when false.
void StatsObserver::TurnOn() {
	_subject->Attach(false, this);
};

// Removes observer in order to stop its view.
void StatsObserver::TurnOff() {
	_subject->Detach(false, this);
};

// Display will print stats on the console depending on where notify is called.
void StatsObserver::display() {
	double mapSize = _subject->getGameMap()->getSize();
	vector<Player*> players = _subject->getPlayers();
	string name = _subject->getPName();

	// Gets the number of territories of each player and divides it by the total number of territories and
	//multiplies by 100 to get the percentage.
	  for (int i = 0; i < players.size(); i++) {
		  cout << players[i]->getPlayerName() << " controls " <<
			  (players[i]->getPlayerTerritories().size())/mapSize * 100 << "% of the map." << endl;
		 
	}


};