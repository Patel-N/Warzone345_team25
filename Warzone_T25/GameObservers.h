#pragma once
#include <list>
#include<vector>
using namespace std;

class GameEngine;

// Super class (abstract class)
class Observer {

public:
    ~Observer();
    virtual void Update() = 0;

protected:
    Observer();
};

// Super class (abstract class)
class Subject {

public:
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject();
    ~Subject();

protected:
    list<Observer*>* _observers;
};

// The Observable object must be a 
// subclass of Subject. (GAME ENGINE)


class PhaseObserver : public Observer {

public:
    PhaseObserver();
    PhaseObserver(GameEngine* s);
    ~PhaseObserver();
    void Update();
    void display();

private:
    GameEngine* _subject;
};

class StatsObserver : public Observer {

public:
    StatsObserver();
    StatsObserver(GameEngine* s);
    ~StatsObserver();
    void Update();
    void display();

private:
    GameEngine* _subject;
};



