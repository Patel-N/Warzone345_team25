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
Player::Player(int id,string name,int initialArmyAmount) : playerId(id),playerName(name),armyToBePlaced(initialArmyAmount){};

Player::Player() {
    playerId = -1;
    playerName = "nullPlayer";
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
    if (obj.getPlayerOrders().size() > 0) {
        output
            << "===========================" << endl
            << "    Player issued orders   " << endl
            << "============================" << endl;
        vector<Order*> orderList = obj.getPlayerOrders();
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

vector<Territory*> Player::toDefend() {// returns list of territory pointers to defend
    //DO PROPER IMPLEMENTATION
    return  { territoryPtr };
};

void Player::removeTerritoryFromList(int territoryIndex) {
    territoryPtr.erase(territoryPtr.begin() + territoryIndex);
}
//method to add players on the diplomacy list of a player
void Player::declareDiplomacy(int playerId) {
    diplomacy.push_back(playerId);
}

//method to clear the diplomacy list
void::Player::clearDiplomacy() {
    diplomacy.clear();
}
vector<int> Player::getDiplomacies() {
    return diplomacy;
}
void Player::assignTerritoryToPlayer(Territory* newTerritory)
{
    territoryPtr.push_back(newTerritory);
};

void Player::issueOrder(Order* order) {
    orderPtr.push_back(order);
   
    /*
    Order* neworder= new Order(); // creating new order and pointer
    list<OrderDUMMY*> temp = { neworder }; //temporary place pointer into a list
    Orderptr.merge(temp);// merg pointer into list of pointer
    */
};
Order* Player::getNextOrder() {
    Order* orderToReturn;
    if (orderPtr.size() > 0) {
        Order* orderToReturn = orderPtr.front();
        orderPtr.erase(orderPtr.begin());//iterator starts at the first element and erases the first element since no increment
        return orderToReturn;
    }
    else {
        return NULL;
    }
    
}

void Player::setPlayerHand(Hand* newHand) {
    handPtr = newHand;
}
