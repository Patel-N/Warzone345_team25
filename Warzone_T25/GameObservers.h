#pragma once
#include <list>
#include<vector>
#include<iostream>
using namespace std;

class GameEngine;

// Super class (abstract class)
class Observer {

public:
    ~Observer();
    virtual void Update() = 0;
    virtual void TurnOn() = 0;

protected:
    Observer();
};

// Super class (abstract class)
class Subject {

public:
    virtual void Attach(bool, Observer* o);
    virtual void Detach(bool, Observer* o);
    virtual void Notify(bool);
    Subject();
    ~Subject();
    //Copy Constructor
    Subject(const Subject& s);
    //Overloaded Assignment Operator
    Subject& operator=(const Subject& s);
   // Overloaded Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const Subject& s);


protected:
    list<Observer*>* phase_observers;
    list<Observer*>* stats_observers;


};

class PhaseObserver : public Observer {

public:
    PhaseObserver();
    PhaseObserver(GameEngine* s);
    ~PhaseObserver();
    void Update();
    void TurnOn();
    void TurnOff();
    void display();
    //Copy Constructor
    PhaseObserver(const PhaseObserver& p);
    //Overloaded Assignment Operator
    PhaseObserver& operator=(const PhaseObserver& p);
    // Overloaded Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const PhaseObserver& p);

private:
    GameEngine* _subject;

};

class StatsObserver : public Observer {

public:
    StatsObserver();
    StatsObserver(GameEngine* s);
    ~StatsObserver();
    void Update();
    void TurnOn();
    void TurnOff();
    void display();
    //Copy Constructor
    StatsObserver(const StatsObserver& p);
    //Overloaded Assignment Operator
    StatsObserver& operator=(const StatsObserver& p);
    // Overloaded Stream Insertion Operator
    friend ostream& operator<<(ostream& out, const StatsObserver& p);

private:
    GameEngine* _subject;
};

namespace part_5 {
    void start();
}
