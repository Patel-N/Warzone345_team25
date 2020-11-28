#pragma once
#include "Player.h"
#include <algorithm>
class PlayerStrategies {
public:

	virtual void  issueOrder() = 0;
	virtual vector<Territory> toDefend() = 0; // returns list of territory pointers to defend
	virtual vector<Territory> toAttack() = 0;// returns list of territory pointers to defend
};

class HumanPlayerStrategy: public PlayerStrategies {
public:
	void issueOrder();
	vector<Territory> toDefend();
	vector<Territory> toAttack();
};

class AggressivePlayerStrategy : public PlayerStrategies {
public:
	void issueOrder();
    vector<Territory> toDefend();
	vector<Territory> toAttack();
};

class BenevolentPlayerStrategy : public PlayerStrategies {
public:
	void issueOrder();
	vector<Territory> toDefend();
	vector<Territory> toAttack();
};

class NeutralPlayerStrategy : public PlayerStrategies {
public:
	void issueOrder();
	vector<Territory> toDefend();
	vector<Territory> toAttack();
};

