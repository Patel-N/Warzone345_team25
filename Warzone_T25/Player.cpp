#pragma once

#include "Player.h"
#include "Map.h"
#include <cstddef>
#include <list>
#include <iostream>
#include <sstream>
#include <string>

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
}


//destructor
Player::~Player() {
    // IMPORTANT: none of the objects player could be holding are deleted
    cout << this->getPlayerName()<<"player destroyed" << endl;
}


//copy constructor
Player::Player(const Player& input) {

    //IMPORTANT: assignment operator and copy constructor will only copy playerId,playerName,armyToBePlaced,
    // or else we will have to duplicate territories objects, card objects, and order objects and might break the game
    playerId = input.playerId;
    playerName = input.playerName;
    armyToBePlaced = input.armyToBePlaced;

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

    //IMPORTANT: assignment operator and copy constructor will only copy playerId,playerName,armyToBePlaced,
    // or else we will have to duplicate territories objects, card objects, and order objects and might break the game
    playerId = input.playerId;
    playerName = input.playerName;
    armyToBePlaced = input.armyToBePlaced;

    return *this;
}

//setters
void Player::setArmyToBePlaced(int count) {
    armyToBePlaced = count;
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
    //DO PROPER IMPLEMENTATION
    return  { territoryPtr };
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
