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

    /*cout << "For " << getPlayerName() << " he can possibly attack " << attackableTerritories.size() << " territories." << endl;
    for (int i = 0; i < attackableTerritories.size(); i++) {
        cout << "Terri id => " << attackableTerritories[i]->getTerritoryID() << "\t || Name => " << attackableTerritories[i]->getName() << "\t || Army count =>" << attackableTerritories[i]->getNumArmies() << endl;
    }*/

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
                        cout << playerTerritories[j]->getNonCommitedArmies() << endl;
                        playerTerritories[j]->decNonCommitedArmies(playerTerritories[j]->getNonCommitedArmies());
                        cout << playerTerritories[j]->getNonCommitedArmies() << endl;
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
            if (getPlayerHand()->getCardsInHand().size() != 0) {
                
                int indexOfCardToPlay;

                //Pick a random card that isn't an airlift
                do {
                    indexOfCardToPlay = rand() % getPlayerHand()->getCardsInHand().size();
                } while (indexOfCardToPlay != 1);

                
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
                        if (!possibleAttack[i]->getIsAttacked()) {
                            t = possibleAttack[i];
                            possibleAttack[i]->setIsAttacked(true);
                            break;
                        }
                    }

                    cout << "Negotiate ==> " << getPlayerName() << " is negotiating with " << t->getPlayer()->getPlayerName() << endl;
                    Negotiate* negotiate = new Negotiate(this, t->getPlayer());
                    orderlist->add(negotiate);

                    //Card returned back to deck
                    getPlayerHand()->play(4, Player::common_deck);
                    setIsCardPlayed(true);

                }//Reinforcement
                else if (card->get_type() == 5) {

                    //cout << "Reinforcement ==> " << getPlayerName() << " is getting an additional 5 units." << endl;
                    //Reinforcement* rein = new Reinforcement(this);
                    //orderlist->add(rein);

                    ////Card returned back to deck
                    //getPlayerHand()->play(5, Player::common_deck);
                    //setIsCardPlayed(true);

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