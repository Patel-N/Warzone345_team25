#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

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
	//Deconstructor
	~Deploy();
	//copy constructor
	Deploy(Order& order);
	//Overloaded Assignment Operator
	Deploy& operator=(Deploy& deploy);
};

class Advance : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Advance();
	~Advance();
	Advance(Order& order);
	//Overloaded Assignment Operator
	Advance& operator=(Advance& advance);
};

class Bomb : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Bomb();
	~Bomb();
	Bomb(Order& order);
	//Overloaded Assignment Operator
	Bomb& operator=(Bomb& bomb);
};


class Blockade : public Order {
public:
	bool validate();
	void execute(int playerIndex);;
	Blockade();
	~Blockade();
	Blockade(Order& order);
	//Overloaded Assignment Operator
	Blockade& operator=(Blockade& blockade);
};

class Airlift : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Airlift();
	~Airlift();
	Airlift(Order& order);
	//Overloaded Assignment Operator
	Airlift& operator=(Airlift& airlift);
};

class Negotiate : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Negotiate();
	~Negotiate();
	Negotiate(Order& order);
	//Overloaded Assignment Operator
	Negotiate& operator=(Negotiate& negotiate);
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
	//Constructor
	OrderList();

	//Copy Constructor
	OrderList(const OrderList& orderlist);

	//Overloaded Assignment Operator
	OrderList& operator=(const OrderList& orderlist);

	//Deconstructor
	~OrderList();


	friend ostream& operator << (ostream& output, OrderList& orderlist);
};
ostream& operator << (ostream& output, Order& order);
ostream& operator << (ostream& output, OrderList& orderlist);

namespace part_4 {
	void start();
}