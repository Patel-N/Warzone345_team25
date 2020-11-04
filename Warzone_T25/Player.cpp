#pragma once

#include "Player.h"
#include "Map.h"

#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;


// player classs is in chard of attac
Player::Player() {};

//copy constructor
Player::Player(const Player& input) {

    //duplicating territory TO REDO!!!
    //for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory
    //    Territory* temptr = new Territory; // creating new territory pointer and territory
    //    temptr->getName() = elm->name; // giving territory same name from input player
    //    list<Territory*> tempList = { temptr }; //temporary place pointer into a list
    //    Territoryptr.merge(tempList);// merg pointer into list of pointer
    //}
    
    //duplicating hand
    handPtr = new Hand; // creating new hand for new player
    vector<Card*> inputCardsInHand = input.handPtr->getCardsInHand();
    for (int i = 0; i < inputCardsInHand.size() ; i++) {// for every card in input player cards
        
        //Call copy ctor
        Card* tempcard = inputCardsInHand[i];
        handPtr->addCardToHand(tempcard);
        //CHECK WITH MARTIN IF I NEED TO KEEP THIS
        //tempcard->name = elm->name; // giving card same name from input player
        //list<CardDUMMY*> tempList = { tempcard }; //temporary place pointer into a list
        //Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
    }


    //duplicating order
    for (auto& elm : input.orderPtr) {// for every order in input player order list
        Order* tempOrder = elm; // creating new order pointer and order
        orderPtr.push_back(tempOrder);

        //CHECK WITH MARTIN IF I NEED TO KEEP THIS
        //temporder->name = elm->name; // giving order same name from input player
        //list<OrderDUMMY*> tempList = { temporder }; //temporary place pointer into a list
        //Orderptr.merge(tempList);// merg pointer into list of pointer
    }
}

//assignment operator overload
Player& Player::operator = (const Player& input) {
    
    // duplicating territory
    /*
    for (auto& elm : input.Territoryptr) {// placing new pointers to with new elements to new player list of territory
        Territory* temptr = new Territory; // creating new territory pointer and territory
        temptr->getName() = elm->name; // giving territory same name from input player
        list<Territory*> tempList = { temptr }; //temporary place pointer into a list
        //Territoryptr.merge(tempList);// merg pointer into list of pointer
    }
    */

    //duplicating hand
    handPtr = new Hand; // creating new hand for new player
    vector<Card*> inputCardsInHand = input.handPtr->getCardsInHand();
    for (int i = 0; i < inputCardsInHand.size(); i++) {// for every card in input player cards

        //Call copy ctor
        Card* tempcard = inputCardsInHand[i];
        handPtr->addCardToHand(tempcard);
        //CHECK WITH MARTIN IF I NEED TO KEEP THIS
        //tempcard->name = elm->name; // giving card same name from input player
        //list<CardDUMMY*> tempList = { tempcard }; //temporary place pointer into a list
        //Handptr->Cardptr.merge(tempList);// merg pointer into list of pointer
    }


    //duplicating order
    for (auto& elm : input.orderPtr) {// for every order in input player order list
        Order* tempOrder = elm; // creating new order pointer and order
        orderPtr.push_back(tempOrder);

        //CHECK WITH MARTIN IF I NEED TO KEEP THIS
        //temporder->name = elm->name; // giving order same name from input player
        //list<OrderDUMMY*> tempList = { temporder }; //temporary place pointer into a list
        //Orderptr.merge(tempList);// merg pointer into list of pointer
    }

    return *this;
}


//stream insertion
istream& operator >> (istream& input, Player& obj) {
    Territory*tempter = new Territory;
    string mystring;
    getline(cin, mystring);
    tempter->getName() = mystring;
    obj.territoryPtr.push_back(tempter);
    return input;
}



ostream &operator << (ostream& output, Player& obj) { // ostream, outputs name of territory of player
    Territory*ter = obj.territoryPtr.front();// accessing territory
    string tername = ter->getName();//save name of that territory
    output << "player has territory: "<< tername << endl;//save that name into output
    return output;
}


vector<Territory*> Player::toDefend() {// returns list of territory pointers to defend
    //DO PROPER IMPLEMENTATION
    return  { territoryPtr };
};

vector<Territory*>Player::toAttack() {// returns list of territory pointers to defend
    //DO PROPER IMPLEMENTATION
    return  { territoryPtr };
}
void Player::assignTerritoryToPlayer(Territory* newTerritory)
{
    territoryPtr.push_back(newTerritory);
};

void Player::issueOrder() {
   
    /*
    Order* neworder= new Order(); // creating new order and pointer
    list<OrderDUMMY*> temp = { neworder }; //temporary place pointer into a list
    Orderptr.merge(temp);// merg pointer into list of pointer
    */
};
    
