#pragma once

#include "Territory.h"
#include "Hand.h"
#include "OrderList.h"
#include "Order.h"
#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


// player classs is in chard of attac
class Player
{
    public:
    list<Territory*> Territoryptr; // list of territory pointers
    Hand* Handptr;// pointer to a hand an object of type Hand associated to a player
    list<Order*> Orderptr; //list of orders pointers


    //copy constructor
    Player(const Player& input) {

        // duplicating territory
        for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory          
            Territory* temptr = new Territory; // creating new territory pointer and territory
            temptr->name = elm->name; // giving territory same name from input player
            list<Territory*> tempList = { temptr }; //temporary place pointer into a list
            Territoryptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating hand
         Handptr = new Hand; // creating new hand for new player
        for (auto& elm : input.Handptr->Cardptr) {// for every card in input player cards       
            Card* tempcard = new Card; // creating new card pointer and card
            tempcard->name = elm->name; // giving card same name from input player
            list<Card*> tempList = { tempcard }; //temporary place pointer into a list
            Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating order
        for (auto& elm : input.Orderptr) {// for every order in input player order list       
            Order* temporder = new Order; // creating new order pointer and order
            temporder->name = elm->name; // giving order same name from input player
            list<Order*> tempList = { temporder }; //temporary place pointer into a list
            Orderptr.merge(tempList);// merg pointer into list of pointer
        }
    }

    //stream insertion
    friend istream& operator >> (istream& input, Player& obj) {
        Territory *tempter = new Territory;
        string mystring;
        getline(cin, mystring);
        tempter->name = mystring; 
        obj.Territoryptr.push_back(tempter);
        return input;
       
    }

    friend ostream &operator << (ostream& output, Player& obj) { // ostream, outputs name of territory of player
        Territory *ter = obj.Territoryptr.front();// accessing territory
        string tername = ter->name;//save name of that territory
        output << "player has territory: "<< tername << endl;//save that name into output
            return output;
    }


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