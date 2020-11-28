#pragma once

#include "Player.h"
#include "Map.h"
#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdlib.h> 


Deck* Player::common_deck = NULL; // initializing static class member. 

using namespace std;

// player classs is in chard of attac
Player::Player(int id,string name,int initialArmyAmount) : playerId(id),playerName(name),armyToBePlaced(initialArmyAmount){
    orderlist = new OrderList();
    isConquerer = false;
};

Player::Player() {
    playerId = -1;
    playerName = "nullPlayer";
    orderlist = new OrderList();
}

Player::Player(int id, string name){
    playerName = name;
    playerId = id;
    orderlist = new OrderList();
};

Player::Player(int id, string name, vector<Territory*> ownedT, Hand* h, vector<Order*> o, int armyCount, int strategy) {
    playerId = id;
    this->playerName = name;
    this->handPtr = h;
    orderlist = new OrderList();

    assignStrategy(strategy);
}

void Player::assignStrategy(int strategy) {

    switch (strategy)
    {
    case 1:
        playerStrategy = new HumanPlayerStrategy();
        break;

    case2:
        playerStrategy = new AggressivePlayerStrategy();
        break;

    case3:
        playerStrategy = new BenevolentPlayerStrategy();
        break;

    case4:
        playerStrategy = new NeutralPlayerStrategy();
        break;

    default:
        break;
    }
}


//destructor
Player::~Player() {
    // IMPORTANT: none of the objects player could be holding are deleted
    cout << this->getPlayerName()<<"player destroyed" << endl;
}


//copy constructor
Player::Player(const Player& input) {

    //IMPORTANT: assignment operator and copy constructor will do a shallow copy. duplicated player
    // will point to the orginal objects, like Territory, Hand, Orders, cards or else it might break the game.

     territoryPtr = input.territoryPtr;
     handPtr = input.handPtr;
     orderlist = input.orderlist;
     playerId = input.playerId;
     playerName = input.playerName;
     armyToBePlaced = input.armyToBePlaced;
     isConquerer = input.isConquerer;
     diplomacy = input.diplomacy;//this member variable serves to add target players for the negotiate order
     defenseApplied = input.defenseApplied;
     attackApplied = input.attackApplied;
     isCardPlayed = input.isCardPlayed;
}

//stream input
istream& operator >> (istream& input, Player& obj) {
    Territory* tempter = new Territory;
    string mystring;
    getline(cin, mystring);
    tempter->getName() = mystring;
    obj.territoryPtr.push_back(tempter);
    return input;
}

//stream output
ostream& operator << (ostream& output, Player& obj) { // ostream, outputs name of territory of player
    output
        << "Player name = " << obj.getPlayerName() << endl
        << "Player id = " << obj.getPlayerId() << endl
        << "Player has " <<obj.getArmyToBePlaced()<<" in his army pool" << endl;
    if (obj.getPlayerTerritories().size() > 0) {
        output
            <<
            "===========================" << endl <<
            "    Player territory list   " << endl <<
            "============================" << endl;
        vector < Territory* > territoryList = obj.getPlayerTerritories();
        for (int i = 0; i < territoryList.size(); i++) {
            output << *territoryList[i] << endl;
        }
    }
    else {
        output
            <<
            "Player does not own territory" << endl;
    }

    if (obj.getPlayerOrders() != NULL && obj.getPlayerOrders()->allOrders.size() > 0) {
        output
            << "===========================" << endl
            << "    Player issued orders   " << endl
            << "============================" << endl;
        vector<Order*> orderList = obj.getPlayerOrders()->allOrders;
        for (int i = 0; i < orderList.size(); i++) {
            output << *orderList[i] << endl;
        }
    }
    else {
        output
            << "Player does not have any issued orders" << endl;
    }
    return output;
}

//assignment operator = overload
Player& Player::operator = (const Player& input) {


    //IMPORTANT: assignment operator and copy constructor will do a shallow copy. duplicated player
    // will point to the orginal objects, like Territory, Hand, Orders, cards or else it might break the game.

    territoryPtr = input.territoryPtr;
    handPtr = input.handPtr;
    orderlist = input.orderlist;
    playerId = input.playerId;
    playerName = input.playerName;
    armyToBePlaced = input.armyToBePlaced;
    isConquerer = input.isConquerer;
    diplomacy = input.diplomacy;//this member variable serves to add target players for the negotiate order
    defenseApplied = input.defenseApplied;
    attackApplied = input.attackApplied;
    isCardPlayed = input.isCardPlayed;

    return *this;
}

//setters
void Player::setArmyToBePlaced(int count) {
    armyToBePlaced = count;
}


vector<Territory*> Player::toAttack() {// returns list of territory pointers to defend
    
  
    //Build a vector of source territory attacking a target territory
    vector<Territory*> attackableTerritories;
   

    vector<Territory*> allTerritories = allTerritoryVectorBuilder(territoryPtr[0]);


    //Remove territories that already belong to the players from the appropriate vector
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

    //Set the state of all the territories to not visited
    for (int i = 0; i < allTerritories.size(); i++) {
        allTerritories[i]->setIsVisited(false);
    }

    sort(attackableTerritories.begin(), attackableTerritories.end(), Territory::compByArmyCount);

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

void Player::setConquererFlag(bool conquererFlag) {
    isConquerer = conquererFlag;
}


void Player::setOrderList(OrderList* list) {
    this->orderlist = list;
}
void Player::addToArmiesToBePlaced(int additionalArmies) {
    armyToBePlaced += additionalArmies;
}


vector<Territory*> Player::toDefend() {// returns list of territory pointers to defend
    
    vector<Territory*> territoryToBeDefended;
    for (int i = 0; i < territoryPtr.size(); i++) {
        territoryToBeDefended.push_back(territoryPtr[i]);
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);

    return territoryToBeDefended;
};

void Player::removeTerritoryFromList(int territoryIndex) {
    for (int i = 0; i < territoryPtr.size();i++) {
        if (territoryPtr[i]->getTerritoryID() - 1 == territoryIndex) {
            territoryPtr.erase(territoryPtr.begin() + i);
        }
    }
}
//method to add players on the diplomacy list of a player
void Player::declareDiplomacy(Player* targetedPlayer) {
    if (targetedPlayer == NULL) { 
        cout << endl << "ERROR: Cannot declare diplomacy on NULL player";
        return;
    }
    else {
       this->addPlayerToDiplomacyList(targetedPlayer->getPlayerId());//by adding targeted player on the diplomacy list of the issuing player,we stop any possible attack from the targeted player
       targetedPlayer->addPlayerToDiplomacyList(this->getPlayerId());//diplomacy goes both ways and hence the issuing player should also not be able to attack target
    }
}

//method to clear the diplomacy list
void::Player::clearDiplomacy() {
    diplomacy.clear();
}
vector<int> Player::getDiplomacies() {
    return diplomacy;
}
void::Player::addPlayerToDiplomacyList(int playerId) {
    diplomacy.push_back(playerId);
}
void Player::assignTerritoryToPlayer(Territory* newTerritory)
{
    territoryPtr.push_back(newTerritory);
};

void Player::issueOrder() {
  
    this->playerStrategy->issueOrder();
};

void Player::deployCreation(vector<Territory*> playerWeakestTerritories,int armyCount) {
    
    
    //Update nonCommitedCount
    for (int i = 0; i < playerWeakestTerritories.size(); i++) {
        
        //Only add if territories hasn't had anything commited to it
        if (playerWeakestTerritories[i]->getNumArmies() == playerWeakestTerritories[i]->getNonCommitedArmies()) {

            //Increment the num of nonCommitedArmies
            playerWeakestTerritories[i]->incNonCommitedArmies(armyCount);

            //Create the order & Update armyToBePlaced cout
            Deploy* d = new Deploy(armyCount, playerWeakestTerritories[i], this);
            orderlist->add(d);
            armyToBePlaced -= armyCount;
            cout << getPlayerName() << " Deploying " << armyCount << " at territory " << playerWeakestTerritories[i]->getTerritoryID() << endl;

            break;
        }

    }

}
    

void Player::issueOrder(Order* order) {
    orderlist->allOrders.push_back(order);
    sortOrderList();
};

void Player::sortOrderList() {
    orderlist->sort();
}
Order* Player::getNextOrder() {
    Order* orderToReturn;
    if (orderlist->allOrders.size() > 0) {
        Order* orderToReturn = orderlist->allOrders.front();
        return orderToReturn;
    }
    else {
        return NULL;
    }    
}

void Player::setPlayerHand(Hand* newHand) {
    handPtr = newHand;
}