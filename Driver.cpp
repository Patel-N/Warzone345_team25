
#include "Orders.h"

int main() {

	//Create OrderList
	OrderList orderlist1;

	orderlist1.add(new Deploy());
	orderlist1.add(new Advance());
	orderlist1.add(new Bomb());
	orderlist1.add(new Blockade());
	orderlist1.add(new Airlift());
	orderlist1.add(new Negotiate());
	
	// checking execution status and order stream overload operator
	cout << orderlist1.allOrders[0] << endl;
	
	//toString, move, remove testing
	//cout << orderlist1;
	orderlist1.move(4,2);
	//cout << orderlist1;
	//orderlist1.remove(2);
	//cout << orderlist1;

	//execute testing
	int numPlayer = 0;
	for (int i = 0; i < orderlist1.numSize; i++) {
		orderlist1.allOrders[i]->execute(numPlayer);
	}

	// checking execution status and order stream overload operator
	cout << endl;
	cout << orderlist1.allOrders[0] << endl;

	// Check copy constructor- deep copy on new objects

	OrderList orderlist2(orderlist1);
	cout << "New OrderList is orderlist2: " << endl;
	cout << orderlist2 << endl;
	cout << "Chaniging orderlist 2 to demonstrate deep copy." << endl;
	orderlist2.move(3, 1);
	orderlist2.remove(4);
	cout << "OrderList2: " << orderlist2 << endl;
	cout << "OrderList1: " << orderlist1 << endl;


	// check overloaded assignment operator - deep copy on already existing object
	OrderList orderlist3;
	cout << "Copying orderlist 1 to 2: " << endl;
	orderlist3 = orderlist1;
	cout << "OrderList3: " << orderlist3 << endl;
	cout << "OrderList1: " << orderlist1 << endl;
	cout << "Now making changes to orderlist3 to demonstrate asssignment overload " << endl;
	orderlist3.move(5, 2);
	orderlist3.remove(4);

	cout << "OrderList3: " << orderlist3 << endl;
	cout << "OrderList1: " << orderlist1 << endl;
	
	
	//delete(orderlist1);
	
	return 0;
}