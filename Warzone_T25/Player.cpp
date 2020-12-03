#pragma once

#include "Player.h"
#include "Map.h"
#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdlib.h> 
//#include "PlayerStrategies.h"
using namespace std;

Deck* Player::common_deck = NULL; // initializing static class member. 

using namespace std;

// player classs is in chard of attac
Player::Player(int id,string name,int initialArmyAmount) : playerId(id),playerName(name),armyToBePlaced(initialArmyAmount){
    orderlist = new OrderList();
    isConquerer = false;
}
Player::Player(int id, string name, int strategy, int toRemove)
{
    playerName = name;
    playerId = id;
    orderlist = new OrderList();
    assignStrategy(strategy);
}

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



void Player::setStrategy(int strategy) {
    assignStrategy(strategy);
}

void Player::assignStrategy(int strategy) {
    cout << endl << "IN STRATEGY" << endl;
    //if the player already has a strategy , we delete before assigning a new one
    if (playerStrategy != NULL) {
        delete playerStrategy;
        playerStrategy = NULL;
    }
    switch (strategy)
    {
    case 1:
        playerStrategy = new HumanPlayerStrategy(this);
        break;

    case 2:
        playerStrategy = new AggressivePlayerStrategy(this);
        break;

    case 3:
        playerStrategy = new BenevolentPlayerStrategy(this);
        break;

    case 4:
        playerStrategy = new NeutralPlayerStrategy(this);
        break;

    default:
        break;
    }
}



//destructor
Player::~Player() {
    // IMPORTANT: none of the objects player could be holding are deleted
    cout << this->getPlayerName()<<"player destroyed" << endl;
    delete playerStrategy;
    delete handPtr;
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
    
    vector<Territory*> toAttackTerr = playerStrategy->toAttack();
    return toAttackTerr;
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
    vector<Territory*> toDefendTerr = this->playerStrategy->toDefend();
    return toDefendTerr;
};

vector<Territory*> Player::getAdjacentTerritoriesOfPlayer(Territory* playerTerritory) {
    vector<Territory*> adjacentTerritoriesOfPlayer;
    if (playerTerritory == NULL || playerTerritory->getTerritoryOccupant() == NULL) { return adjacentTerritoriesOfPlayer; }
    if (this->getPlayerId() != playerTerritory->getTerritoryOccupant()->getPlayerId()) {
        return adjacentTerritoriesOfPlayer;
    }
    else {
        vector<Territory*> adjacentTerritories = playerTerritory->getAdjacentTerritories();
        for (int i = 0; i < adjacentTerritories.size(); i++) {
            if (adjacentTerritories[i]->getTerritoryOccupant() == NULL) { continue; }
            if (adjacentTerritories[i]->getTerritoryOccupant()->getPlayerId() == this->getPlayerId()) {
                adjacentTerritoriesOfPlayer.push_back(adjacentTerritories[i]);
            }
        }
    }
    return adjacentTerritoriesOfPlayer;
}

vector<Territory*> Player::getNonAdjacentTerritoriesOfPlayer(Territory* playerTerritory) {
    vector<Territory*> nonAdjacentTerritoriesOfPlayer;
    if (playerTerritory == NULL || playerTerritory->getTerritoryOccupant() == NULL) { return nonAdjacentTerritoriesOfPlayer; }
    if (this->getPlayerId() != playerTerritory->getTerritoryOccupant()->getPlayerId()) {
        return nonAdjacentTerritoriesOfPlayer;
    }
    else {
        vector<Territory*> playerTerritoriesToDefend = this->toDefend();
        vector<Territory*> adjacentTerritoriesOfPlayer = getAdjacentTerritoriesOfPlayer(playerTerritory);
        bool isAdj = false;
        for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
            Territory* territoryInAllFriendlyTerritoryList = playerTerritoriesToDefend[i];
            for (int j = 0; j < adjacentTerritoriesOfPlayer.size(); j++) {
                Territory* territoryInAdjacentFriendlyTerritories = adjacentTerritoriesOfPlayer[j];
                if ((territoryInAllFriendlyTerritoryList->getTerritoryID() == territoryInAdjacentFriendlyTerritories->getTerritoryID())) {
                    isAdj = true;
                    continue;
                }
            }
            //we make sure the territory we are adding is not adjacent nor the same as the strongest territory
            if (!isAdj && playerTerritoriesToDefend[i]->getTerritoryID() != playerTerritory->getTerritoryID()) {
                nonAdjacentTerritoriesOfPlayer.push_back(playerTerritoriesToDefend[i]);
            }
            isAdj = false;
        }
    }
    return nonAdjacentTerritoriesOfPlayer;
}
vector<Territory*> Player::getAdjacentTerritoriesToAttack(Territory* playerTerritory)
{
    vector<Territory*> adjTerritoriesToAttack;
    if (playerTerritory == NULL || playerTerritory->getTerritoryOccupant() == NULL) { return adjTerritoriesToAttack; }
    if (this->getPlayerId() != playerTerritory->getTerritoryOccupant()->getPlayerId()) {
        return adjTerritoriesToAttack;
    }
    else {
        vector<Territory*> toAttack = this->toAttack();
        vector<Territory*> adjTerr = playerTerritory->getAdjacentTerritories();
        for (int i = 0; i < toAttack.size(); i++) {
            Territory* territoryToAttackInAllEnemyTerritories = toAttack[i];
            for (int j = 0; j < adjTerr.size(); j++) {
                Territory* adjacenTerritory = adjTerr[j];
                if (territoryToAttackInAllEnemyTerritories->getTerritoryID() == adjacenTerritory->getTerritoryID()) {
                    if (territoryToAttackInAllEnemyTerritories->getTerritoryID() == 7) { cout << endl << "PUSHING THE WRONG TERR " << endl; }
                    adjTerritoriesToAttack.push_back(territoryToAttackInAllEnemyTerritories);
                }
            }
        }
    }
    return adjTerritoriesToAttack;
}
vector<Territory*>Player::getNonAdjacentTerritoriesToAttack(Territory* playerTerritory) {
    vector<Territory*> nonAdjacentTerritoriesToAttack;
    if (playerTerritory == NULL || playerTerritory->getTerritoryOccupant() == NULL) { return nonAdjacentTerritoriesToAttack; }
    if (this->getPlayerId() != playerTerritory->getTerritoryOccupant()->getPlayerId()) {
        return nonAdjacentTerritoriesToAttack;
    }
    else {
        vector<Territory*> playerTerritoriesToAttack = this->toAttack();
        vector<Territory*> adjacentTerritoriesToAttack = getAdjacentTerritoriesToAttack(playerTerritory);
        bool isAdj = false;
        for (int i = 0; i < playerTerritoriesToAttack.size(); i++) {
            Territory* territoryInAllEnemyTerritoryList = playerTerritoriesToAttack[i];
            for (int j = 0; j < adjacentTerritoriesToAttack.size(); j++) {
                Territory* territoryInAdjacentEnemyTerritories = adjacentTerritoriesToAttack[j];
                if ((territoryInAllEnemyTerritoryList->getTerritoryID() == territoryInAdjacentEnemyTerritories->getTerritoryID())) {
                    isAdj = true;
                    continue;
                }
            }
            //we make sure the territory we are adding is not adjacent nor the same as the strongest territory
            if (!isAdj && playerTerritoriesToAttack[i]->getTerritoryID() != playerTerritory->getTerritoryID()) {
                nonAdjacentTerritoriesToAttack.push_back(playerTerritoriesToAttack[i]);
            }
            isAdj = false;
        }
    }
    return nonAdjacentTerritoriesToAttack;
}
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