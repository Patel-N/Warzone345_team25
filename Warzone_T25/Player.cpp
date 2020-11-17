#pragma once

#include "Player.h"

#include "Map.h"

#include <cstddef>

#include <list>

#include <iostream>

#include <sstream>

#include <string>


using namespace std;

// constructors
Player::Player(int id, string name) : playerId(id), playerName(name) {};

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
        <<
        "Player name = " << obj.getPlayerName() << endl <<
        "Player id = " << obj.getPlayerId() << endl;
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

vector < Territory* > Player::toDefend() { // returns list of territory pointers to defend
  //todo
    return {
      territoryPtr
    };
};

vector < Territory* > Player::toAttack() { // returns list of territory pointers to defend



    //todo

    return {
      territoryPtr
    };
}

void Player::assignTerritoryToPlayer(Territory* newTerritory) {
    territoryPtr.push_back(newTerritory);
};

void Player::issueOrder() {

    //todo
};