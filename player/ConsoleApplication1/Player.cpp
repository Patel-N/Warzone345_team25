
#include "Player.h"
#include "Territory.h"
#include "Hand.h"
#include "OrderList.h"
#include "Order.h"
#include <cstddef>
#include <list>
using namespace std;


// player classs is in chard of attac
class Player
{
    public:
    list<Territory*> Territoryptr; // list of territory pointers
    Hand* Handptr;// pointer to a hand an object of type Hand associated to a player
    list<Order*> Orderptr; //list of orders pointers

    list<Territory*> toDefend() {// returns list of territory pointers to defend
        return  { Territoryptr }; 
    };

    list<Territory*> toAttack() {// returns list of territory pointers to defend
        return  { Territoryptr };
    };

    void issueOrder() {   
       Order* neworder= new Order(); // creating new order and pointer
       list<Order*> temp = { neworder }; //temporary place pointer into a list
       Orderptr.merge(temp);// merg pointer into list of pointer
    };
};