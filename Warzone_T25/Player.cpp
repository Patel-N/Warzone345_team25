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

Player::Player(int id, string name, vector<Territory*> ownedT, Hand* h, vector<Order*> o, int armyCount) {
    playerId = id;
    this->playerName = name;
    this->handPtr = h;
    orderlist = new OrderList();
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
    

    //Player shouldn't be able to call other orders if they still have deployable armies
    if (getArmyToBePlaced() != 0) {
        
        vector<Territory*> playerWeakestTerritories = toDefend();

        //Split through the least having territories
        int splitCount = getArmyToBePlaced() / territoryPtr.size();
        //Determine if you want to assign a split amount of territories or the full amount
        if (splitCount > getArmyToBePlaced()) {
            deployCreation(playerWeakestTerritories, splitCount);
        }
        else { //Deploy every unit remaining
            deployCreation(playerWeakestTerritories, getArmyToBePlaced());
        }
        
    }
    //No more army to deploy, followup with next order
    else {

        //The reverse order of this are territories with the most army units to attack with
        vector<Territory*> playerTerritories = toDefend();
        vector<Territory*> ennemyTerritories = toAttack();

        

        //Handle advance orders
        if (!getAttackApplied()) {

            for (int i = 0; i < ennemyTerritories.size(); i++) {

                for (int j = playerTerritories.size() - 1; j >= 0; j--) {

                    //Compare unit count and check if territory wasnt attacked already
                    if (!ennemyTerritories[i]->getIsAttacked() && ennemyTerritories[i]->getNonCommitedArmies() < playerTerritories[j]->getNonCommitedArmies()) {

                        //Check if the territory is adjacent
                        vector<Territory*> currentTerAdj = playerTerritories[j]->getAdjacentTerritories();
                        bool isAdj = false;

                        for (int k = 0; k < currentTerAdj.size(); k++) {
                            if (currentTerAdj[k]->getTerritoryID() == ennemyTerritories[i]->getTerritoryID()) {
                                isAdj = true;
                                break;
                            }
                        }

                        //Regular advance
                        if (isAdj) {
                            cout << "Advance(Attack) ==> " << getPlayerName() << " is moving " << playerTerritories[j]->getNonCommitedArmies() << " units to territory -> " << ennemyTerritories[i]->getTerritoryID() << " from ID " << playerTerritories[j]->getTerritoryID() << endl;
                            Advance* adv = new Advance(playerTerritories[j]->getNonCommitedArmies(), playerTerritories[j], ennemyTerritories[i], this);
                            playerTerritories[j]->decNonCommitedArmies(playerTerritories[j]->getNonCommitedArmies());
                            orderlist->add(adv);
                            //Mark as the current territory as it moved its army already
                            playerTerritories[j]->setWasAdvanced(true);

                            //Mark the ennemy territory as being attacked already
                            ennemyTerritories[i]->setIsAttacked(true);
                        }
                        else { //requires airlift
                            
                            //Check if player has an airlift card
                            if (getPlayerHand()->getCardsInHand().size() != 0 && getPlayerHand()->isCardInHand(1)) {
                                cout << "Airlift ==> " << getPlayerName() << " is moving " << playerTerritories[j]->getNonCommitedArmies() << " units to territory -> " << ennemyTerritories[i]->getTerritoryID() << " from ID " << playerTerritories[j]->getTerritoryID() << endl;
                                Airlift* alift = new Airlift(playerTerritories[j]->getNonCommitedArmies(), playerTerritories[j], ennemyTerritories[i], this);
                                playerTerritories[j]->decNonCommitedArmies(playerTerritories[j]->getNonCommitedArmies());
                                orderlist->add(alift);

                                //Card returned back to deck
                                getPlayerHand()->play(1, Player::common_deck);

                                //Mark as the current territory as it moved its army already
                                playerTerritories[j]->setWasAdvanced(true);

                                //Mark the ennemy territory as being attacked already
                                ennemyTerritories[i]->setIsAttacked(true);
                            }
                        }

                    }

                }

                if (i == ennemyTerritories.size() - 1) {
                    setAttackApplied(true);
                }
            }
        
        }
        else if (!getDefenseApplied()) {
        
            //Check if there are armies available to be moved from one player territory to another
            for (int i = 0; i < playerTerritories.size(); i++) {
                
                for (int j = playerTerritories.size() - 1; j >= 0; j--) {
                    //Move armies if greater amount
                    if (!playerTerritories[j]->getWasAdvanced() && playerTerritories[j]->getNonCommitedArmies() > playerTerritories[i]->getNonCommitedArmies()) {
                        cout << "Advance(Defence) ==> " << getPlayerName() << " is moving " << playerTerritories[j]->getNonCommitedArmies() << " units to territory -> " << playerTerritories[i]->getTerritoryID() << " from ID " << playerTerritories[j]->getTerritoryID() << endl;
                        Advance* adv = new Advance(playerTerritories[j]->getNonCommitedArmies(), playerTerritories[j], playerTerritories[i], this);
                        playerTerritories[j]->decNonCommitedArmies(playerTerritories[j]->getNonCommitedArmies());
                        orderlist->add(adv);

                        //Mark as the current territory as it moved its army already
                        playerTerritories[j]->setWasAdvanced(true);
                    }

                }
                
                if (i == playerTerritories.size() - 1) {
                    setDefenseApplied(true);
                }

            }

            
        } else if(!getIsCardPlayed()){
            //Won't do anything if hand is empty
            if (getPlayerHand()->getCardsInHand().size() != 0 && !(getPlayerHand()->getCardsInHand().size() == 1 && getPlayerHand()->getCardsInHand()[0]->get_type() == 1)) {
                int indexOfCardToPlay;
                //Pick a random card that isn't an airlift
                for (int i = 0; i < getPlayerHand()->getCardsInHand().size(); i++) {
                    if (getPlayerHand()->getCardsInHand()[i]->get_type() != 1) {
                        indexOfCardToPlay = i;
                    }
                }
               
                Card* card = handPtr->getCardsInHand()[indexOfCardToPlay];

                //Bomb
                if (card->get_type() == 2) {

                    vector<Territory*> possibleAttack = toAttack();
                    Territory* t = new Territory();

                    //Get the highest unit count ennemy territory
                    for (int i = possibleAttack.size() - 1; i >= 0; i-- ) {
                        if (!possibleAttack[i]->getIsAttacked()) {
                            t = possibleAttack[i];
                            possibleAttack[i]->setIsAttacked(true);
                            break;
                        }
                    }

                    cout << "Bomb ==> " << getPlayerName() << " is bombing " << t->getTerritoryID() << endl;
                    Bomb* bAttack = new Bomb(this,t);
                    orderlist->add(bAttack);

                    //Card returned back to deck
                    getPlayerHand()->play(2, Player::common_deck);
                    setIsCardPlayed(true);

                }//Blockade
                else if (card->get_type() == 3) {

                    Territory* t = territoryPtr[0];

                    //Loop through player territory to find the biggest value of army
                    for (int i = 1; i < territoryPtr.size(); i++) {
                        if (t->getNonCommitedArmies() < territoryPtr[i]->getNonCommitedArmies()) {
                            t = territoryPtr[i];
                        }
                    }

                    cout << "Blockade ==> " << getPlayerName() << " is blockading " << t->getTerritoryID() << endl;
                    Blockade* blockade = new Blockade(this, t);
                    orderlist->add(blockade);

                    //Card returned back to deck
                    getPlayerHand()->play(3, Player::common_deck);
                    setIsCardPlayed(true);
                
                }//Diplomacy
                else if (card->get_type() == 4) {
                    vector<Territory*> possibleAttack = toAttack();
                    Territory* t = new Territory();

                    //Get the highest unit count ennemy territory
                    for (int i = possibleAttack.size() - 1; i >= 0; i--) {
                        if (!possibleAttack[i]->getIsAttacked() && possibleAttack[i]->getPlayer() != NULL) {
                            t = possibleAttack[i];
                            possibleAttack[i]->setIsAttacked(true);
                            break;
                        }
                    }

                    if (t->getTerritoryContinentID() != 0) {
                        cout << "Negotiate ==> " << getPlayerName() << " is negotiating with " << t->getPlayer()->getPlayerName() << endl;
                        Negotiate* negotiate = new Negotiate(this, t->getPlayer());
                        orderlist->add(negotiate);

                        //Card returned back to deck
                        getPlayerHand()->play(4, Player::common_deck);
                    }
                    setIsCardPlayed(true);

                }//Reinforcement
                else if (card->get_type() == 5) {

                    cout << "Reinforcement ==> " << getPlayerName() << " is getting an additional 5 units." << endl;
                    Reinforcement* rein = new Reinforcement(this);
                    orderlist->add(rein);

                    //Card returned back to deck
                    getPlayerHand()->play(5, Player::common_deck);
                    setIsCardPlayed(true);

                }

            }
            else {
                setIsCardPlayed(true);
            }

        }
        else {
            Commit* c = new Commit();
            orderlist->add(c);
        }
        
    }
    

};

void Player::deployCreation(vector<Territory*> playerWeakestTerritories,int armyCount) {
    
    
    //Update nonCommitedCount
    for (int i = 0; i < playerWeakestTerritories.size(); i++) {
        cout << "Territory ==> " << playerWeakestTerritories[i]->getName() << "Current => " << playerWeakestTerritories[i]->getNumArmies() << " || Predicted => " << playerWeakestTerritories[i]->getNonCommitedArmies() << endl;
        
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