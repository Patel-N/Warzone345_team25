#include "GameObservers.h"
#include <iostream>

// OBSSERVER CLASS
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
};

void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

void Subject::Notify() {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
};

// CLOCK TIMER CLASS
ClockTimer::ClockTimer() : hour(0), minute(0), second(0) {
};

ClockTimer::~ClockTimer() {
};

void ClockTimer::start() {
	for (int i = 1; i <= timedInterval; i++)
		tick();
};

void ClockTimer::tick() {
	second++;
	if (second >= 60) {
		minute++; second = 0;
		if (minute >= 60) {
			hour++; minute = 0;
			if (hour >= 24) {
				hour = 0;
			}
		}
	};
	// Any time its state changes, 
	// the Observable object notifies 
	// all its registered observers       
	Notify();
};

// DIGITAL CLOCK CLASS
DigitalClock::DigitalClock() {
};

DigitalClock::DigitalClock(ClockTimer* s) {
	//Upon instantiation, attaches itself 
	//to a ClockTimer
	_subject = s;
	_subject->Attach(this);
};

DigitalClock::~DigitalClock() {
	//Upon destruction, detaches itself 
	//from its ClockTimer      
	_subject->Detach(this);
};

void DigitalClock::Update() {
	//Called by Notify() when state of Subject changes
	display();
};

void DigitalClock::display() {
	int hour = _subject->getHour();
	int minute = _subject->getMinute();
	int second = _subject->getSecond();
	int interval = _subject->getInterval();
	cout << hour << ":" << minute << ":" << second << "(" << interval << ")" << endl;
};

// CLOCK CONTROLLER CLASS
ClockController::ClockController(DigitalClock* newView, ClockTimer* newModel) {
	clockView = newView;
	clockModel = newModel;
}

void ClockController::controlClock() {
	while (true) {
		int command;
		cout << "1. Set the timer's start time (1 int int int <return>)" << endl;
		cout << "2. Set the timer's timed interval (2 int <return>)" << endl;
		cout << "3. Start the timer (3 <return>)" << endl;
		cout << "4. Exit (4 <return>)" << endl;
		cout << "Enter action (1,2,3,4) : ";
		cin >> command;
		switch (command) {
		case 1:
			int h, m, s;
			cin >> h >> m >> s;
			clockModel->setTime(h, m, s);
			break;
		case 2:
			int t;
			cin >> t;
			clockModel->setTimedInterval(t);
			break;
		case 3:
			clockModel->start();
			break;
		case 4:
			return;
		}
	}
}
