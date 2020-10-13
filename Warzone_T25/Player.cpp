#pragma once

#include "TerritoryDUMMY.h"
#include "HandDUMMY.h"
#include "OrderListDUMMY.h"
#include "OrderDUMMY.h"
#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include "Player.h"

using namespace std;


// player classs is in chard of attac

   


    //copy constructor
    Player::Player() {};
    Player::Player(const Player& input) {

        // duplicating territory
        for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory          
            TerritoryDUMMY* temptr = new TerritoryDUMMY; // creating new territory pointer and territory
            temptr->name = elm->name; // giving territory same name from input player
            list<TerritoryDUMMY*> tempList = { temptr }; //temporary place pointer into a list
            Territoryptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating hand
         Handptr = new HandDUMMY; // creating new hand for new player
        for (auto& elm : input.Handptr->Cardptr) {// for every card in input player cards       
            CardDUMMY* tempcard = new CardDUMMY; // creating new card pointer and card
            tempcard->name = elm->name; // giving card same name from input player
            list<CardDUMMY*> tempList = { tempcard }; //temporary place pointer into a list
            Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating order
        for (auto& elm : input.Orderptr) {// for every order in input player order list       
            OrderDUMMY* temporder = new OrderDUMMY; // creating new order pointer and order
            temporder->name = elm->name; // giving order same name from input player
            list<OrderDUMMY*> tempList = { temporder }; //temporary place pointer into a list
            Orderptr.merge(tempList);// merg pointer into list of pointer
        }
    }

    //assignment operator overload
    Player& Player::operator = (const Player& input) {
        // duplicating territory
        for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory          
            TerritoryDUMMY* temptr = new TerritoryDUMMY; // creating new territory pointer and territory
            temptr->name = elm->name; // giving territory same name from input player
            list<TerritoryDUMMY*> tempList = { temptr }; //temporary place pointer into a list
            Territoryptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating hand
        Handptr = new HandDUMMY; // creating new hand for new player
        for (auto& elm : input.Handptr->Cardptr) {// for every card in input player cards       
            CardDUMMY* tempcard = new CardDUMMY; // creating new card pointer and card
            tempcard->name = elm->name; // giving card same name from input player
            list<CardDUMMY*> tempList = { tempcard }; //temporary place pointer into a list
            Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
        }
        //duplicating order
        for (auto& elm : input.Orderptr) {// for every order in input player order list       
            OrderDUMMY* temporder = new OrderDUMMY; // creating new order pointer and order
            temporder->name = elm->name; // giving order same name from input player
            list<OrderDUMMY*> tempList = { temporder }; //temporary place pointer into a list
            Orderptr.merge(tempList);// merg pointer into list of pointer
        }



        return *this;

    }


    //stream insertion
     istream& operator >> (istream& input, Player& obj) {
        TerritoryDUMMY*tempter = new TerritoryDUMMY;
        string mystring;
        getline(cin, mystring);
        tempter->name = mystring; 
        obj.Territoryptr.push_back(tempter);
        return input;
       
    }

  

     ostream &operator << (ostream& output, Player& obj) { // ostream, outputs name of territory of player
        TerritoryDUMMY*ter = obj.Territoryptr.front();// accessing territory
        string tername = ter->name;//save name of that territory
        output << "player has territory: "<< tername << endl;//save that name into output
            return output;
    }


    list<TerritoryDUMMY*> Player::toDefend() {// returns list of territory pointers to defend
        return  { Territoryptr }; 
    };

    list<TerritoryDUMMY*>Player::toAttack() {// returns list of territory pointers to defend
        return  { Territoryptr };
    };

    void Player::issueOrder() {   
       OrderDUMMY* neworder= new OrderDUMMY(); // creating new order and pointer
       list<OrderDUMMY*> temp = { neworder }; //temporary place pointer into a list
       Orderptr.merge(temp);// merg pointer into list of pointer

    };
