#pragma once
#include <algorithm>
#include<iostream>
using namespace std;

class Player;

class PlayerStrategies { //abstract class
public:

	virtual void  issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0; // returns list of territory pointers to defend
	virtual vector<Territory*> toAttack() = 0;// returns list of territory pointers to defend

};

class HumanPlayerStrategy: public PlayerStrategies {
public:
	HumanPlayerStrategy(Player*);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*>  toAttack();
private:
	Player* strategyExecuter;
};

class AggressivePlayerStrategy : public PlayerStrategies {
public:
	AggressivePlayerStrategy(Player*);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	//getters
	inline Player*  getStrategyExecuter() { return strategyExecuter; }
	//other helper methods
	bool deployStrategy(Territory*);
	bool movingFriendlyTroopsAroundStrategy(Territory*);
	bool movingAdjacentTroops(Territory*);
	bool movingDistantTroops(Territory*);
	bool attackStrategy(Territory*);
private:
	Player* strategyExecuter;
};

class BenevolentPlayerStrategy : public PlayerStrategies {
public:
	BenevolentPlayerStrategy(Player*);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	//getters
	inline Player* getStrategyExecuter() { return strategyExecuter; }
private:
	Player* strategyExecuter;
};

class NeutralPlayerStrategy : public PlayerStrategies {
public:
	NeutralPlayerStrategy(Player*);
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	//getters
	inline Player* getStrategyExecuter() { return strategyExecuter; }
private:
	 Player* strategyExecuter;
};

