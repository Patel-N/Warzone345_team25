#pragma once
#include<iostream>
#include<string>
#include<vector>


using namespace std;

class Player;
class Territory;

class Order { // abstract class- no instantiation. // no pointer or objects so no requirement of assignment operator and copy constructor
private:
	string orderName;
	bool orderState;
public:
	string getorderName();
	bool getorderState();
	void setorderName(string name);
	void setorderState(bool flag);
	virtual bool validate() = 0;
	virtual void execute(int playerIndex) = 0;
	friend ostream& operator << (ostream& output, Order& order);
	//Constructor
	Order();
	//Deconstructor
	virtual ~Order() { cout << "Order Deconstructed " << endl; };
	//Copy Constructor
	Order(const Order& order);
	//Overloaded Assignment Operator
	Order& operator=(const Order& order);
};

class Deploy : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	//Constructor
	Deploy();
	Deploy(int, Territory*,Player*);
	//Deconstructor
	~Deploy();
	//copy constructor
	Deploy(Order& order);
	//Overloaded Assignment Operator
	Deploy& operator=(Deploy& deploy);
private:
	int armiesToDeploy;
	Territory* target;
	Player* issuingPlayer;
};

class Advance : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	void move();
	vector<int> attack();
	void conquer(vector<int>);
	void defeatDamageControl(vector<int>);
	bool isDiplomacyDeclared();
	void displayBattleComposition(int);
	void DisplayBattleResult(vector<int>);
	vector<int> runBattleMechanics(int);
	Advance();
	Advance(int, Territory*, Territory*, Player*);
	~Advance();
	Advance(Order& order);
	//Overloaded Assignment Operator
	Advance& operator=(Advance& advance);
private:
	int armiesToAdvance;
	Territory* target;
	Territory* source;
	Player* issuingPlayer;
};

class Bomb : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	void displayBombResult();
	Bomb();
	Bomb(Player*, Territory*);
	~Bomb();
	Bomb(Order& order);
	//Overloaded Assignment Operator
	Bomb& operator=(Bomb& bomb);
private:
	Player* issuingPlayer;
	Territory* target;
};


class Blockade : public Order {
public:
	bool validate();
	void execute(int);
	void displayBlockedTerritory();
	Blockade(Player*,Territory*);
	Blockade();
	~Blockade();
	Blockade(Order& order);
	//Overloaded Assignment Operator
	Blockade& operator=(Blockade& blockade);
private:
	Player* issuingPlayer;
	Territory* targetTerritory;
};

class Airlift : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	void move();
	vector<int> attack();
	void conquer(vector<int>);
	void defeatDamageControl(vector<int>);
	bool isDiplomacyDeclared();
	void displayBattleComposition(int);
	void DisplayBattleResult(vector<int>);
	vector<int> runBattleMechanics(int);
	Airlift();
	Airlift(int, Territory*, Territory*, Player*);
	~Airlift();
	Airlift(Order& order);
	//Overloaded Assignment Operator
	Airlift& operator=(Airlift& airlift);
private:
	int armiesToAdvance;
	Territory* target;
	Territory* source;
	Player* issuingPlayer;
};

class Negotiate : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	void displayDiplomacies();
	Negotiate();
	Negotiate(Player*, Player*);
	~Negotiate();
	Negotiate(Order& order);
	//Overloaded Assignment Operator
	Negotiate& operator=(Negotiate& negotiate);
private:
	Player* issuingPlayer;
	Player* targetPlayer;
};

class Commit : public Order {

public:
	bool validate();
	void execute(int playerIndex);

	//Ctor
	Commit();

	//Dtor
	~Commit();

	//Copy ctor
	Commit(Order& commit);

	//Overloaded Assignment Op
	Commit& operator=(Commit& input);

};


class OrderList {
public:
	vector<Order*> allOrders;
	int numSize;

	// Insert a new order
	void add(Order* order);
	void print();
	void move(int fromPos, int toPos);
	void remove(int numRem);
	void sort();
	//Constructor
	OrderList();

	//Copy Constructor
	OrderList(const OrderList& orderlist);

	//Overloaded Assignment Operator
	OrderList& operator=(const OrderList& orderlist);

	//Deconstructor
	~OrderList();

	string peekLastOrder();
	friend ostream& operator << (ostream& output, OrderList& orderlist);
};
ostream& operator << (ostream& output, Order& order);
ostream& operator << (ostream& output, OrderList& orderlist);

namespace part_4 {
	void start();
}