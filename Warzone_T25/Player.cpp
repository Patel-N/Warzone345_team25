#pragma once

#include "Player.h"
#include "Map.h"

#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>


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

vector<Territory*> Player::toAttack() {// returns list of territory pointers to defend
    
  
    //Build a vector of source territory attacking a target territory
    vector<Territory*> attackableTerritories;
   
    ////Iterate through all territories owned by a player
    //for (int i = 0; i < territoryPtr.size(); i++) {

    //    //Get List of adjacent territories
    //    vector<Territory*> gdt = territoryPtr[i]->getAdjacentTerritories();

    //    cout << "\tTerritory => " << territoryPtr[i] << " With id => " << territoryPtr[i]->getTerritoryID() << endl;


    //    //Iterate through adjacent territories of a specific territories 
    //    for (int j = 0; j < gdt.size(); j++) {
    //        cout << "\t\tSubterritory id => " << gdt[j] << " with ID => " << gdt[j]->getTerritoryID();
    //        bool isUnique = true;

    //       
    //        //Check the diff between armies of the territories they could potentially attack
    //        int armyDifference = territoryPtr[i]->getNumArmies() - gdt[j]->getNumArmies();
    //        cout << " || The army diff is => " << armyDifference << endl;

    //        //Create attacking option
    //        TerritoryAttackDefend* attackProposal = new TerritoryAttackDefend(territoryPtr[i], gdt[j], armyDifference);

    //        //Add if the vector not empty
    //        if (allPlayerAdjacentTerritory.size() == 0) {
    //            allPlayerAdjacentTerritory.push_back(gdt[j]);
    //        }

    //        //Check if territory is already in the adjacent vector
    //        for (int k = 0; k < allPlayerAdjacentTerritory.size(); k++) {

    //            //Check if new territory is already part of the unique adjacent vector
    //            if (gdt[j]->getTerritoryID() == allPlayerAdjacentTerritory[k]->getTerritoryID()) {
    //                isUnique = false;

    //                //Loop through attacking options to update
    //                for (int l = 0; l < attackOptions.size(); l++) {
    //                    //3 conditions (same target id, greater diff, territory doesn't belong to same player)
    //                    if (attackOptions[l]->getTargetTerritory()->getTerritoryID() == gdt[j]->getTerritoryID() &&
    //                        attackProposal->getArmyDiff() > attackOptions[l]->getArmyDiff() &&
    //                        attackProposal->getSourceTerritory()->getPlayer() != attackProposal->getTargetTerritory()->getPlayer()) {

    //                        //Update
    //                        attackOptions[l]->setTargetTerritory(attackProposal->getTargetTerritory());
    //                        attackOptions[l]->setArmyDiff(attackProposal->getArmyDiff());

    //                    }

    //                }
    //            }

    //        }

    //        //Add if unique
    //        if (isUnique) {
    //            //Add to vector
    //            allPlayerAdjacentTerritory.push_back(gdt[j]);
    //            
    //            //Add to options 
    //            if (attackProposal->getSourceTerritory()->getPlayer() != attackProposal->getTargetTerritory()->getPlayer()) {
    //                attackOptions.push_back(attackProposal);
    //            }
    //        }

    //    }
    //}

    ////Sort vector
    //sort(attackOptions.begin(), attackOptions.end(), TerritoryAttackDefend::compByArmyDiff);
    //

    ////CHECK NODE LIST
    //cout << endl << endl;
    //for (int i = 0; i < attackOptions.size(); i++) {
    //    cout << "Source terri " << attackOptions[i]->getSourceTerritory()->getTerritoryID() << " || Target terri "  << attackOptions[i]->getTargetTerritory()->getTerritoryID() << " || Army diff " << attackOptions[i]->getArmyDiff() << endl;
    //}

    vector<Territory*> allTerritories = allTerritoryVectorBuilder(territoryPtr[0]);

    for (int i = 0; i < allTerritories.size(); i++) {
    
        bool isEnnemyTerritory = true;

        for (int j = 0; j < territoryPtr.size(); j++) {
        
            if (allTerritories[i]->getTerritoryID() == territoryPtr[j]->getTerritoryID())
                isEnnemyTerritory = false;
        }

        if (isEnnemyTerritory) {
            attackableTerritories.push_back(allTerritories[i]);
        }

    }

    sort(attackableTerritories.begin(), attackableTerritories.end(), Territory::compByArmyCount);

    for (int i = 0; i < attackableTerritories.size(); i++) {
        cout << "Terri id => " << attackableTerritories[i]->getTerritoryID() << "\t || Name => " << attackableTerritories[i]->getName() << "\t || Army count =>" << attackableTerritories[i]->getNumArmies() << endl;
    }

    return attackableTerritories;
}

vector<Territory*> Player::allTerritoryVectorBuilder(Territory* origin) {
    
    vector<Territory*> terriBuilder;
    
    //Check if territory is visited
    if (!origin->getIsVisited()) {
        
        //Set the territory as visited and add it to the vector
        origin->setIsVisited(true);
        terriBuilder.push_back(origin);

        //Loop through its adjacent territories recursively
        for (int i = 0; i < origin->getAdjacentTerritories().size(); i++) {
            vector<Territory*> subterritoryVector = allTerritoryVectorBuilder(origin->getAdjacentTerritories()[i]);
            terriBuilder.insert(terriBuilder.end(), subterritoryVector.begin(), subterritoryVector.end());
        }

    }

    //vector<Territory*> currentAdjacent = origin->getAdjacentTerritories();
    sort(terriBuilder.begin(), terriBuilder.end(), Territory::compById);

    
    return terriBuilder;
}


vector<Territory*> Player::toDefend() {// returns list of territory pointers to defend
    
    vector<Territory*> territoryToBeDefended;
    for (int i = 0; i < territoryPtr.size(); i++) {
        territoryToBeDefended.push_back(new Territory(*territoryPtr[i]));
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);

    return territoryToBeDefended;
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
    


