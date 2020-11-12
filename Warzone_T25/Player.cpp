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

Player::Player() {
    playerId = -1;
    playerName = "nullPlayer";
}

Player::Player(int id, string name) : playerId(id), playerName(name) {};

Player::Player(int id, string name, vector<Territory*> ownedT, Hand* h, vector<Order*> o, int armyCount) {
    playerId = id;
    this->playerName = name;
    this->handPtr = h;
    this->orderPtr = o;
    

}

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
    output
        << "Player name = " << obj.getPlayerName() << endl
        << "Player id = " << obj.getPlayerId() << endl;
    if (obj.getPlayerTerritories().size() > 0) {
        output
        << "===========================" << endl
        << "    Player territory list   " << endl
        << "============================" << endl;
        vector<Territory*> territoryList = obj.getPlayerTerritories();
        for (int i = 0; i < territoryList.size(); i++) {
            output << *territoryList[i] << endl;
        }
    }
    else {
        output
            << "Player does not own territory" << endl;
    }
    return output;
}


void Player::setArmyToBePlaced(int count)
{
    armyToBePlaced = count;
}

vector<Territory*>Player::toAttack() {// returns list of territory pointers to defend
    
    TerritoryAttackDefend* head = new TerritoryAttackDefend();
    
    //Potentially become toAttack list

    vector<Territory*> allPlayerAdjacentTerritory;
    vector<TerritoryAttackDefend*> attackOptions;
    //Get List of adjacent territories
    //Iterate through all territories owned by a player

    cout << "\t" << territoryPtr.size() << endl;
    for (int i = 0; i < territoryPtr.size(); i++) {
        vector<Territory*> gdt = territoryPtr[i]->getAdjacentTerritories();

        cout << "\tTerritory => " << territoryPtr[i] << " With id => " << territoryPtr[i]->getTerritoryID() << endl;


        //Iterate through adjacent territories of a specific territories 
        for (int j = 0; j < gdt.size(); j++) {
            cout << "\t\tSubterritory id => " << gdt[j] << " with ID => " << gdt[j]->getTerritoryID();
            bool isUnique = true;

           
            //Check the diff between armies of the territories they could potentially attack
            int armyDifference = territoryPtr[i]->getNumArmies() - gdt[j]->getNumArmies();
            cout << " || The army diff is => " << armyDifference << endl;

            //Create attacking option
            TerritoryAttackDefend* attackProposal = new TerritoryAttackDefend(territoryPtr[i], gdt[j], armyDifference);

            //Add if make the vector not empty
            if (allPlayerAdjacentTerritory.size() == 0) {
                allPlayerAdjacentTerritory.push_back(gdt[j]);
            }

            //Check if territory is already in the adjacent vector
            for (int k = 0; k < allPlayerAdjacentTerritory.size(); k++) {

                //Check if new territory is already part of the unique adjacent vector
                if (gdt[j]->getTerritoryID() == allPlayerAdjacentTerritory[k]->getTerritoryID()) {
                    isUnique = false;

                    //Loop through attacking options to update
                    for (int l = 0; l < attackOptions.size(); l++) {
                        //3 conditions (same target id, greater diff)
                        if (attackOptions[l]->getTargetTerritory()->getTerritoryID() == gdt[j]->getTerritoryID() &&
                            attackProposal->getArmyDiff() > attackOptions[l]->getArmyDiff() &&
                            attackProposal->getSourceTerritory()->getPlayer() != attackProposal->getTargetTerritory()->getPlayer() &&
                            gdt[j]->getPlayer() != NULL) {

                            //Update
                            attackOptions[l]->setTargetTerritory(attackProposal->getTargetTerritory());
                            attackOptions[l]->setArmyDiff(attackProposal->getArmyDiff());

                        }

                    }
                }

            }

            //Add if unique
            if (isUnique) {
                //Add to vector
                allPlayerAdjacentTerritory.push_back(gdt[j]);
                
                //Add to options if it is owned by another player
                if (gdt[j]->getPlayer() != NULL && attackProposal->getSourceTerritory()->getPlayer() != attackProposal->getTargetTerritory()->getPlayer()) {
                    attackOptions.push_back(attackProposal);
                }
            }

        }
    }

    

    /*cout << "THE SIZE OF ADJACENT UNIQUE VECTOR => " << allPlayerAdjacentTerritory.size() << endl;
    for (int i = 0; i < allPlayerAdjacentTerritory.size(); i++) {
        cout << allPlayerAdjacentTerritory[i]->getTerritoryID() << endl;
    }*/
    

    //CHECK NODE LIST
    cout << endl << endl;
    for (int i = 0; i < attackOptions.size(); i++) {
        cout << "Source terri " << attackOptions[i]->getSourceTerritory()->getTerritoryID() << " || Target terri "  << attackOptions[i]->getTargetTerritory()->getTerritoryID() << " || Army diff " << attackOptions[i]->getArmyDiff() << endl;
    }
    
    return  { territoryPtr };
}

vector<Territory*> Player::toDefend() {// returns list of territory pointers to defend
    //DO PROPER IMPLEMENTATION
    return  { territoryPtr };
};

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
    


