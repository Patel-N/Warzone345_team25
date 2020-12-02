#pragma once
#include <algorithm>
#include<iostream>
using namespace std;

class Player;

class PlayerStrategies {
public:
	virtual ~PlayerStrategies(){ }
	PlayerStrategies(){}
	virtual void  issueOrder() = 0;
	virtual vector<Territory*> toDefend() = 0; // returns list of territory pointers to defend
	virtual vector<Territory*> toAttack() = 0;// returns list of territory pointers to defend
private:
	Player* strategyExecuter;

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
	AggressivePlayerStrategy(const AggressivePlayerStrategy&);
	~AggressivePlayerStrategy();
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	//getters
	inline Player*  getStrategyExecuter() { return strategyExecuter; }
	//other helper methods
	bool deployStrategy(Territory*);
	bool movingFriendlyTroopsAroundStrategy(Territory*);
	bool attackStrategy(Territory*);
	bool playCardsStrategy(Territory*);
	AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy&);
	friend ostream& operator<<(ostream& outs, const AggressivePlayerStrategy& theObject);
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
	NeutralPlayerStrategy(const NeutralPlayerStrategy&);
	~NeutralPlayerStrategy();
	void issueOrder();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	//getters
	inline Player* getStrategyExecuter() { return strategyExecuter; }
	NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy&);
	friend ostream& operator<<(ostream& outs, const NeutralPlayerStrategy& theObject);
private:
	 Player* strategyExecuter;
};

