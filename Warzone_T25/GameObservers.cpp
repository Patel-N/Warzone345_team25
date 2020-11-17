#include "GameObservers.h"
#include "GameEngine.h"

#include <iostream>

// OBSERVER CLASS
Observer::Observer() {

}

Observer::~Observer() {

}

// SUBJECT CLASS
Subject::Subject() {
	_observers = new list<Observer*>;
}

Subject::~Subject() {
	delete _observers;
}

void Subject::Attach(Observer* o) {
	_observers->push_back(o);
	cout << endl << "ADDRESS OF OBSERVER LIST POINTER IN ATTACH" << _observers << endl;
};

void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

void Subject::Notify() {
	cout << endl << "ADDRESS OF OBSERVER LIST POINTER IN NOTIFY " << _observers << endl;
	list<Observer*>::iterator it = _observers->begin();
	for (auto i = _observers->begin(); i != _observers->end(); ++i) {
		cout << "MOHAMMEEEEEEEEEED" << endl;
		(*i)->Update();
	}
};

// PHASE OBSERVER CLASS
PhaseObserver::PhaseObserver() {
};

PhaseObserver::PhaseObserver(GameEngine* s) {
	//Upon instantiation, attaches itself 
	//to a GameEngine
	cout << "PHASEOBSERVER CALLED!!" << endl;
	_subject = s;
	 _subject->Attach(this);
};

PhaseObserver::~PhaseObserver() {
	//Upon destruction, detaches itself 
	//from its GameEngine 
	_subject->Detach(this);
};


void PhaseObserver::Update() {
	//Called by Notify() when state of Subject changes

	display();
};

void PhaseObserver::display() {
	//int hour = _subject->getHour();
	//int minute = _subject->getMinute();
	//int second = _subject->getSecond();
	//int interval = _subject->getInterval();
	//cout << hour << ":" << minute << ":" << second << "(" << interval << ")" << endl;
	//Map* map = _subject->getGameMap();
	//vector<Player*> players = _subject->getPlayers();
	cout << "-------CURRENT MAP VISHALLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL-------\n\n" <</* map*/  "\n\n";
};




// STATS OBSERVER CLASS
StatsObserver::StatsObserver() {
};

StatsObserver::StatsObserver(GameEngine* s) {
	//Upon instantiation, attaches itself 
	//to a ClockTimer
	_subject = s;
	_subject->Attach(this);
};

StatsObserver::~StatsObserver() {
	//Upon destruction, detaches itself 
	//from its ClockTimer      
	_subject->Detach(this);
};

void StatsObserver::Update() {
	//Called by Notify() when state of Subject changes
	display();
};

void StatsObserver::display() {
	//int hour = _subject->getHour(); 
	//int minute = _subject->getMinute();
	//int second = _subject->getSecond();
	//int interval = _subject->getInterval();
	//cout << hour << ":" << minute << ":" << second << "(" << interval << ")" << endl;
	//Map* map = _subject->getGameMap();
	//vector<Player*> players = _subject->getPlayers();
	//cout << "CURRENT MAP" <<
};