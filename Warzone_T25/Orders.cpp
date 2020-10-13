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
Order::Order(const Order& order) {
	(*this).setorderState(order.orderState);
	(*this).setorderName(order.orderName);
}

//OverLoaded Assignment Operator
Order& Order::operator=(const Order& order) {
	(*this).setorderState(order.orderState);
	(*this).setorderName(order.orderName);
	return *this;
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

Deploy::Deploy(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Deploy& Deploy::operator=(Deploy& deploy) {
	if (this == &deploy) {
		return *this;
	}
	(*this).setorderState(deploy.getorderState());
	(*this).setorderName(deploy.getorderName());
	return *this;
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
Advance::Advance(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Advance& Advance::operator=(Advance& advance) {
	if (this == &advance) {
		return *this;
	}
	(*this).setorderState(advance.getorderState());
	(*this).setorderName(advance.getorderName());
	return *this;
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
Bomb::Bomb(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Bomb& Bomb::operator=(Bomb& bomb) {
	if (this == &bomb) {
		return *this;
	}
	(*this).setorderState(bomb.getorderState());
	(*this).setorderName(bomb.getorderName());
	return *this;
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
Blockade::Blockade(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Blockade& Blockade::operator=(Blockade& blockade) {
	if (this == &blockade) {
		return *this;
	}
	(*this).setorderState(blockade.getorderState());
	(*this).setorderName(blockade.getorderName());
	return *this;
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
Airlift::Airlift(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Airlift& Airlift::operator=(Airlift& airlift) {
	if (this == &airlift) {
		return *this;
	}
	(*this).setorderState(airlift.getorderState());
	(*this).setorderName(airlift.getorderName());
	return *this;
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
Negotiate::Negotiate(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Negotiate& Negotiate::operator=(Negotiate& negotiate) {
	if (this == &negotiate) {
		return *this;
	}
	(*this).setorderState(negotiate.getorderState());
	(*this).setorderName(negotiate.getorderName());
	return *this;
}

ostream& operator << (ostream& output, Order& order) {
	if (order.getorderState() == false) {
		output << "The order name is: " << order.getorderName() << " and the order has not been exectuted yet. " << endl;
	}
	if (order.getorderState() == true) {
		output << "The order name is: " << order.getorderName() << " and the order has been exectuted." << endl;
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
			allOrders.push_back(new Deploy(*orderlist.allOrders[i]));
			//allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "advance") {
			allOrders.push_back(new Advance(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "bomb") {
			allOrders.push_back(new Bomb(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "negotiate") {
			allOrders.push_back(new Negotiate(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "blockade") {
			allOrders.push_back(new Blockade(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "airlift") {
			allOrders.push_back(new Airlift(*orderlist.allOrders[i]));
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
	cout << "Overloaded Assignment Operator (deep copy): " << endl;
	if (this == &orderlist) {
		return *this;
	}
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
