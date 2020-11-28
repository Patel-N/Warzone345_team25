#pragma once
#include <algorithm>
#include<iostream>
using namespace std;

class Player;

class PlayerStrategies {
public:

	virtual void  issueOrder() = 0;
	virtual void toDefend() = 0; // returns list of territory pointers to defend
	virtual void toAttack() = 0;// returns list of territory pointers to defend
};

class HumanPlayerStrategy: public PlayerStrategies {
public:
	HumanPlayerStrategy();
	void issueOrder();
	void toDefend();
	void toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategies {
public:
	AggressivePlayerStrategy();
	void issueOrder();
	void toDefend();
	void toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategies {
public:
	BenevolentPlayerStrategy();
	void issueOrder();
	void toDefend();
	void toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategies {
public:
	NeutralPlayerStrategy();
	void issueOrder();
	void toDefend();
	void toAttack();
};

