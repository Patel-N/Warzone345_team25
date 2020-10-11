
#include "Orders.h"

using namespace std;
using std::cout;

int main() {

	//Create OrderList
	OrderList orderlist1;
	
		Order* deploy = new Deploy();
		Order* advance = new Advance();
		Order* bomb = new Bomb();
		Order* blockade = new Blockade();
		Order* airlift = new Airlift();
		Order* negotiate = new Negotiate(); 
	orderlist1.add(*deploy);
	orderlist1.add(*bomb);
	orderlist1.add(*advance);
	orderlist1.add(*blockade);
	orderlist1.add(*airlift);
	orderlist1.add(*negotiate);

	cout << orderlist1;
	cout << "Hello" << endl;
	cout << "this is interesting" << endl;

	return 0;
	
}