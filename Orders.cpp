#include "Orders.h"

//Order
string Order::getorderName() {
	return this->orderName;
}
bool Order::getorderState() {
	return orderState;
}
void Order::setorderName(string name) {
	orderName = name;
}
void Order::setorderState(bool flag) {
	orderState = flag;
}
//Constructor 
Order::Order() {
	setorderName("order");
	setorderState(false);
	cout << "Order Constructed: " << endl;
}


//Deploy
bool Deploy::validate() {
	return true; // condition to validate is not set yet
}
void Deploy::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Deploy Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
	else {
		setorderState(false); // Order Has not been executed- as couldnt be validated
	}
}
//Constructor 
Deploy::Deploy() {
	setorderName("deploy");
	setorderState(false);
	cout << "Deploy Constructed: " << endl;
}

Deploy::~Deploy() {
	cout << "Deploy De-constructed: " << endl;
}

// Advance
bool Advance::validate() {
	return true;
}
void Advance::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Advance Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}
//Constructor 
Advance::Advance() {
	setorderName("advance");
	setorderState(false);
	cout << "Advance Constructed: " << endl;
}
//De-constructor 
Advance::~Advance() {
	cout << "Advance De-constructed: " << endl;
}

// Bomb
bool Bomb::validate() {
		return true;
}
void Bomb::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Bomb Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}
//Constructor 
Bomb::Bomb() {
	setorderName("bomb");
	setorderState(false);
	cout << "Bomb Constructed: " << endl;
}
//De-constructor 
Bomb::~Bomb() {
	cout << "Bomb De-constructed: " << endl;
}

//Blockade
bool Blockade::validate() {
	return true;
}
void Blockade::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Blockade Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}
//Constructor 
Blockade::Blockade() {
	setorderName("blockade");
	setorderState(false);
	cout << "Blockade Constructed: " << endl;
}
//De-constructor 
Blockade::~Blockade() {
	cout << "Blockade De-constructed: " << endl;
}


// Airlift
bool Airlift::validate() {
		return true;
}
void Airlift::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Airlift Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}
//Constructor 
Airlift::Airlift() {
	setorderName("airlift");
	setorderState(false);
	cout << "Airlift Constructed: " << endl;
}
//De-constructor 
Airlift::~Airlift() {
	cout << "Airlift De-constructed: " << endl;
}

// Negotiate
bool Negotiate::validate() {
	return true;
}
void Negotiate::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Negotiate Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}
//Constructor 
Negotiate::Negotiate() {
	setorderName("negotiate");
	setorderState(false);
	cout << "Negotiate Constructed: " << endl;
}
//De-constructor 
Negotiate::~Negotiate() {
	cout << "Negotiate De-constructed: " << endl;
}

ostream& operator << (ostream& output, Order& order) {
	output << "The order name is: " << order.getorderName() << "and the state of the order is :" << order.getorderState() << endl;
	return output;
}
 
// OrderList
void OrderList::add(const Order& order) {
	if (numSize == 10) {
		cout << "Max capacity of orders reached" << endl;
	}
	else {
		allOrders[numSize + 1] = order;
		numSize++;
	}
}
void OrderList::print() {
	for (int i = 0; i < numSize; i++) {
		cout << allOrders[i].getorderName() << endl;
	}
}
void OrderList::move(int fromPos, int toPos) {
	Order* temp = &allOrders[fromPos];
	allOrders[fromPos] = allOrders[toPos];
	allOrders[toPos] = *temp;
}
void OrderList::remove(int numRem) {
	for (int i = numRem; i < numSize; i++) {
		allOrders[numRem] = allOrders[numRem + 1];
	}
	numSize--;
}
// Constructor
OrderList::OrderList() {
	allOrders = new Order[10]; // max number of commands allowed right now...
	numSize = 0;
}
// Copy Constructor
OrderList::OrderList(const OrderList& orderlist) {
	cout << "Copy Constructor: " << endl;
	this->numSize = orderlist.numSize;
	this->allOrders = new Order[10];
	copy(orderlist.allOrders, orderlist.allOrders + numSize, this->allOrders);
}
//OverLoaded Assignment Operator
OrderList& OrderList::operator=(const OrderList& orderlist) {
	cout << "OverLoaded Assignment Called: " << endl;
	if (this == &orderlist) {
		return *this;
	}
	this->numSize = orderlist.numSize;
	copy(orderlist.allOrders, orderlist.allOrders + numSize, this->allOrders);
	return *this;
}

// Destructor`
OrderList::~OrderList() {
	cout << "Destructor Called for OrderList." << endl;
	delete[] allOrders;
}

ostream& operator << (ostream& output, OrderList& orderlist) {
	output << "Order-list has following orders: " << endl <<"| ";
	for (int i = 0; i < orderlist.numSize; i++) {
		output << orderlist.allOrders[i].getorderName()<< " | ";
	}
	output << endl;
	return output;
}


