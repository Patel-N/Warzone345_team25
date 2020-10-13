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

ostream& operator << (ostream& output, Order* order) {
	if (order->getorderState() == false) {
		output << "The order name is: " << order->getorderName() << " and the order has not been exectuted yet. " << endl;
	}
	if (order->getorderState() == true) {
		output << "The order name is: " << order->getorderName() << " and the order has been exectuted." << endl;
	}
	return output;
}

// OrderList
void OrderList::add(Order* order) {
	allOrders.push_back(order);
	numSize++;
}
void OrderList::print() {
	for (int i = 0; i < numSize; i++) {
		cout << allOrders[i]->getorderName() << endl;
	}
}
void OrderList::move(int fromPos, int toPos) {
	allOrders.insert(allOrders.begin() + (toPos - 1), allOrders[fromPos - 1]);
	allOrders.erase(allOrders.begin() + fromPos);

}
void OrderList::remove(int numRem) {
	delete(allOrders[numRem - 1]);
	allOrders.erase(allOrders.begin() + (numRem - 1));
	numSize--;
}
// Constructor
OrderList::OrderList() {
	// max number of commands allowed right now...
	numSize = 0;
}
// Copy Constructor- deep copy
OrderList::OrderList(const OrderList& orderlist) {
	cout << "Copy Constructor (deep copy): " << endl;
	numSize = orderlist.numSize;
	for (int i = 0; i < numSize; i++) {
		if (orderlist.allOrders[i]->getorderName() == "deploy") {
			allOrders.push_back(new Deploy());
			//allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "advance") {
			allOrders.push_back(new Advance);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "bomb") {
			allOrders.push_back(new Bomb);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "negotiate") {
			allOrders.push_back(new Negotiate);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "blockade") {
			allOrders.push_back(new Blockade);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "airlift") {
			allOrders.push_back(new Airlift);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
	}
}
////OverLoaded Assignment Operator
//OrderList& OrderList::operator=(const OrderList& orderlist) {
//	cout << "OverLoaded Assignment Called: " << endl;
//	if (this == &orderlist) {
//		return *this;
//	}
//	this->numSize = orderlist.numSize;
//	for (int i = 0; i < numSize; i++) {
//		Order* copy(orderlist.allOrders[i]);
//		allOrders[i] = copy;
//	}
//	return *this;
//}

////OverLoaded Assignment Operator
OrderList& OrderList::operator=(const OrderList& orderlist) {
	cout << "Copy Constructor (deep copy): " << endl;
	numSize = orderlist.numSize;
	for (int i = 0; i < numSize; i++) {
		if (orderlist.allOrders[i]->getorderName() == "deploy") {
			allOrders.push_back(new Deploy);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "advance") {
			allOrders.push_back(new Advance);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "bomb") {
			allOrders.push_back(new Bomb);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "negotiate") {
			allOrders.push_back(new Negotiate);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "blockade") {
			allOrders.push_back(new Blockade);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "airlift") {
			allOrders.push_back(new Airlift);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}

	}
	return *this;
}

// Destructor
OrderList::~OrderList() {
	cout << "Destructor Called for OrderList." << endl;
	for (unsigned int i = 0; i < allOrders.size(); i++) {
		delete(allOrders[i]);
	}
}

ostream& operator << (ostream& output, OrderList& orderlist) {
	output << "Order-list has following orders: " << endl << "| ";
	for (unsigned int i = 0; i < orderlist.allOrders.size(); i++) {
		output << orderlist.allOrders[i]->getorderName() << " | ";
	}
	output << endl;
	return output;
}


