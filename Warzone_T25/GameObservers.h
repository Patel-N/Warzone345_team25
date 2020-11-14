#pragma once
#include <list>
using namespace std;

class Observer {

public:
	~Observer();
	virtual void Update() = 0;

protected:
	Observer();
};

class Subject {

public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();

private:
	list<Observer*>* _observers;
};

// The Observable object must be a 
// subclass of Subject.
class ClockTimer : public Subject {

public:
    ClockTimer();
    int getHour() { return hour; };
    int getMinute() { return minute; };
    int getSecond() { return second; };
    int getInterval() { return timedInterval; };
    void start();
    void setTimedInterval(int newTimedInterval);
    void setTime(int newH, int newM, int newS);
    void tick();
    ~ClockTimer();

private:
    int hour;
    int minute;
    int second;
    int timedInterval;
};

class DigitalClock : public Observer {

public:
    DigitalClock();
    DigitalClock(ClockTimer* s);
    ~DigitalClock();
    void Update();
    void display();

private:
    ClockTimer* _subject;
};

class ClockController {

private:
    DigitalClock* clockView;
    ClockTimer* clockModel;

public:
    ClockController(DigitalClock* newView, ClockTimer* newModel);
    void controlClock();
};

