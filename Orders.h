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
	virtual bool validate() = 0 ;
	virtual void execute(int playerIndex) = 0;
	friend ostream& operator << (ostream& output, Order* order);
	//Constructor
	Order();
	//Deconstructor
	virtual ~Order() { cout << "Order Deconstructed " << endl; };

};

class Deploy : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	//Constructor
	Deploy();
	//Deconstructor
	~Deploy();

};

class Advance : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Advance();
	~Advance();

};

class Bomb : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Bomb();
	~Bomb();
};


class Blockade : public Order {
public:
	bool validate();
	void execute(int playerIndex);;
	Blockade();
	~Blockade();
};

class Airlift : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Airlift();
	~Airlift();
};

class Negotiate : public Order {

public:
	bool validate();
	void execute(int playerIndex);
	Negotiate();
	~Negotiate();
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
ostream& operator << (ostream& output, Order* order);
ostream& operator << (ostream& output, OrderList& orderlist);