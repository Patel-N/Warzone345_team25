
#include "Player.h"
#include "Map.h"
#include<iostream>
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* executer) {
    this->strategyExecuter = executer;
    cout << endl << "AGGRESSIVE PLAYER STRATEGY CREATED" << endl;
}
/* //Split through the least having territories
 int splitCount = getArmyToBePlaced() / territoryPtr.size();
 //Determine if you want to assign a split amount of territories or the full amount
 if (splitCount > getArmyToBePlaced()) {
     deployCreation(playerWeakestTerritories, splitCount);
 }
 else { //Deploy every unit remaining
     deployCreation(playerWeakestTerritories, getArmyToBePlaced());
 }*/

 //}
/*

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
        bool advDone = false;
        bool advDefDone = false;


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

                            //Made an attack so I should exit
                            advDone = true;
                            break;
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

                                //Made an attack so I should exit
                                advDone = true;
                                break;
                            }
                        }

                    }

                }

                if (i == ennemyTerritories.size() - 1) {
                    setAttackApplied(true);
                }

                //exit if order is executed
                if (advDone)
                    break;

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

                        advDefDone = true;
                    }

                }

                //exit if order is executed
                if (advDefDone)
                    break;

                if (i == playerTerritories.size() - 1) {
                    setDefenseApplied(true);
                }

            }


        }
        else if (!getIsCardPlayed()) {
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
                    for (int i = possibleAttack.size() - 1; i >= 0; i--) {
                        if (!possibleAttack[i]->getIsAttacked()) {
                            t = possibleAttack[i];
                            possibleAttack[i]->setIsAttacked(true);
                            break;
                        }
                    }

                    cout << "Bomb ==> " << getPlayerName() << " is bombing " << t->getTerritoryID() << endl;
                    Bomb* bAttack = new Bomb(this, t);
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

    }*/

AggressivePlayerStrategy::~AggressivePlayerStrategy() {
    cout << endl << "Aggressive strategy object destroyed" << endl;
}

void AggressivePlayerStrategy::issueOrder() {
    cout << endl << "===============================" << endl;
    cout << endl << " AGGRESSIVE ISSUE ORDER CALLED " << endl;
    cout << endl << "===============================" << endl;
    cout << endl << "Looking for strongest Territory...." << endl;
    vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    int maxArmyTerritoryIndex = 0;
    int maxArmy = 0;
    for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
        if (playerTerritoriesToDefend[i]->getNumArmies() > maxArmy) {
            maxArmy = playerTerritoriesToDefend[i]->getNumArmies();
            maxArmyTerritoryIndex = i;
        }
    }
    Territory* strongestTerritory = playerTerritoriesToDefend[maxArmyTerritoryIndex];
    cout << endl << "strongest Territory Found... Here is the strongest territory of aggressive Player " << strategyExecuter->getPlayerName() << endl;
    cout << *strongestTerritory << endl;
    cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " attempting to deploy troops..." << endl;
    bool deployOrderCreated, moveFromFriendlyOrderCreated, attackOrderCreated, cardsPlayed = false;
    deployOrderCreated = deployStrategy(strongestTerritory);//argument = strongest territory
    if (deployOrderCreated) {
        cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " has deployed troops" << endl;
    }
    else {
        cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " was not able to deploy troops" << endl;
    }
    if (!deployOrderCreated) {
        cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " attempting to move troops around..." << endl;
        moveFromFriendlyOrderCreated = movingFriendlyTroopsAroundStrategy(strongestTerritory);
        if (!moveFromFriendlyOrderCreated) {
            cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " Attempting to create attacks..." << endl;
            attackOrderCreated = attackStrategy(strongestTerritory);
            if (!attackOrderCreated) {
                cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " not able to create attacks" << endl;
                cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << "attempting at using cards..." << endl;
                cardsPlayed = playCardsStrategy(strongestTerritory);
                if (cardsPlayed) { cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " successful at creating orders with cards" << endl; }
                else { cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " was not able to create orders with cards" << endl; }
            }
            else { cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " succesffully issued attack orders" << endl; }
        }
        else { cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " successfully issued order to move troops around" << endl; }
    }
    if (!deployOrderCreated && !moveFromFriendlyOrderCreated && !attackOrderCreated && !cardsPlayed) {
        Commit* commit = new Commit();
        strategyExecuter->getOrderList()->add(commit);
    }
    cout << endl << "===============================" << endl;
    cout << endl << " AGGRESSIVE ISSUE ORDER DONE " << endl;
    cout << endl << "===============================" << endl;

}

bool AggressivePlayerStrategy::deployStrategy(Territory* strongestTerritory) {
    // Everytime issue order is called, we verify if a deploy order can still be issued
    bool orderCreated = false;
    if (this->strategyExecuter->getArmyToBePlaced() != 0) {
        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
        //the aggressive player would want to advance on its stronger territory 
        cout << endl << "Available armies in pool: " << this->strategyExecuter->getArmyToBePlaced() << endl;
        cout << endl << "Deploying " << this->strategyExecuter->getArmyToBePlaced() << " on strongest territory " << strongestTerritory->getName() << " ID# " << strongestTerritory->getTerritoryID() << endl;
        Deploy* d = new Deploy(this->strategyExecuter->getArmyToBePlaced(), strongestTerritory, strategyExecuter);
        strategyExecuter->getOrderList()->add(d);
        strategyExecuter->addToArmiesToBePlaced(-this->strategyExecuter->getArmyToBePlaced());
        orderCreated = true;
    }
    else {
        return orderCreated;
    }
}

bool AggressivePlayerStrategy::movingFriendlyTroopsAroundStrategy(Territory* strongestTerritory) {
    cout << endl << "IN HERE" << endl;
    vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    vector<Territory*> adjacentTerritories = strongestTerritory->getAdjacentTerritories();
    vector<Territory*> adjacentTerritoriesOfPlayer = strategyExecuter->getAdjacentTerritoriesOfPlayer(strongestTerritory);
    vector<Territory*> nonAdjacentTerritoriesOfPlayer = strategyExecuter->getNonAdjacentTerritoriesOfPlayer(strongestTerritory);
    bool orderCreated = false;
    for (int i = 0; i < adjacentTerritoriesOfPlayer.size(); i++) {
        Territory* adjTerritory = adjacentTerritoriesOfPlayer[i];
        if (adjTerritory->getNonCommitedArmies() > 1) {
            //we leave one army behind, and move the rest to the strongest territory by creating an advance order
            int armiesToMove = adjTerritory->getNonCommitedArmies() - 1;
            if (!orderCreated) {
                cout << endl << "Aggressive player moving " << armiesToMove << " armies from " << adjTerritory->getName() << " to " << strongestTerritory->getName() << endl;
                Order* advanceOrder = new Advance(armiesToMove, adjTerritory, strongestTerritory, strategyExecuter);
                strategyExecuter->getOrderList()->add(advanceOrder);
                adjTerritory->decNonCommitedArmies(armiesToMove);
                orderCreated = true;
                return orderCreated;
            }
        }
    }
    bool isAirliftCardInHand = strategyExecuter->getPlayerHand()->isCardInHand(1);
    if (isAirliftCardInHand) {
        for (int i = 0; i < nonAdjacentTerritoriesOfPlayer.size(); i++) {
            Territory* friendlyTerritoryThatRequiresAirlift = nonAdjacentTerritoriesOfPlayer[i];
            if (friendlyTerritoryThatRequiresAirlift->getNonCommitedArmies() > 1) {
                int armiesToAirlift = friendlyTerritoryThatRequiresAirlift->getNonCommitedArmies() - 1;
                if (!orderCreated) {
                    cout << endl << "Aggressive player airlifting " << armiesToAirlift << " armies from " << friendlyTerritoryThatRequiresAirlift->getName() << " to " << strongestTerritory->getName() << endl;
                    Order* airliftOrder = new Airlift(armiesToAirlift, friendlyTerritoryThatRequiresAirlift, strongestTerritory, strategyExecuter);
                    strategyExecuter->getOrderList()->add(airliftOrder);
                    friendlyTerritoryThatRequiresAirlift->decNonCommitedArmies(armiesToAirlift);
                    //removing card from hand
                    strategyExecuter->getPlayerHand()->play(1, Player::common_deck);
                    orderCreated = true;
                    return orderCreated;
                }
            }
        }
    }
    return false;
}

bool AggressivePlayerStrategy::attackStrategy(Territory* strongestTerritory) {
    vector<Territory*> territoriesToAttack = strategyExecuter->toAttack();
    vector<Territory*> adjTerritoriesToAttack = strategyExecuter->getAdjacentTerritoriesToAttack(strongestTerritory);
    vector<Territory*> nonAdjacentTerritoriesToAttack = strategyExecuter->getNonAdjacentTerritoriesToAttack(strongestTerritory);
    bool isOrderCreated = false;
    //verify if strongest territory has troop to advance to enemy territories
    if (strongestTerritory->getNonCommitedArmies() > 1) {
        //advance on adjacent territory if possible
        if (adjTerritoriesToAttack.size() > 0) {
            //randomnly picking the first adjacent territory in the list: the list is sorted so the first territory is garuantied to be weaker
            Territory* territoryToAttack = adjTerritoriesToAttack[0];
            int ArmiesToMarch = strongestTerritory->getNonCommitedArmies() - 1;
            cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << "About to issue attack order..." << endl;
            cout << endl << "Available armies to attack with from strong territory: " << strongestTerritory->getNonCommitedArmies() << " armies " << endl;
            cout << endl << "Attacking with: " << ArmiesToMarch << " armies " << endl;
            strongestTerritory->decNonCommitedArmies(ArmiesToMarch);
            Order* advanceOrder = new Advance(ArmiesToMarch, strongestTerritory, territoryToAttack, strategyExecuter);
            strategyExecuter->getOrderList()->add(advanceOrder);
            isOrderCreated = true;
            return isOrderCreated;
        }
        bool isAirliftInHand = strategyExecuter->getPlayerHand()->isCardInHand(1);
        if (isAirliftInHand) {
            Territory* territoryToAttack = nonAdjacentTerritoriesToAttack[0];
            int armiesToAirlift = strongestTerritory->getNonCommitedArmies() - 1;
            Order* airliftOrder = new Airlift(armiesToAirlift, strongestTerritory, territoryToAttack, strategyExecuter);
            strategyExecuter->getOrderList()->add(airliftOrder);
            strategyExecuter->getPlayerHand()->play(1, Player::common_deck);
            isOrderCreated = true;
            return isOrderCreated;
        }
    }
    return false;
}

bool AggressivePlayerStrategy::playCardsStrategy(Territory* strongestTerritory) {
    vector<Territory*> territoriesToAttack = strategyExecuter->toAttack();
    vector<Territory*> adjTerritoriesToAttack = strategyExecuter->getAdjacentTerritoriesToAttack(strongestTerritory);
    vector<Territory*> nonAdjacentTerritoriesToAttack = strategyExecuter->getNonAdjacentTerritoriesToAttack(strongestTerritory);
    bool orderCreated = false;
    if (strategyExecuter->getPlayerHand() != NULL) {
        Hand* playerHand = strategyExecuter->getPlayerHand();
        for (int i = 0; i < playerHand->getCardsInHand().size(); i++) {
            Card* card = playerHand->getCardsInHand()[i];
            if (card->get_type() == 1) { continue; }
            else {
                if (card->get_type() == 2) {
                    Territory* terrToBomb = nonAdjacentTerritoriesToAttack[0];
                    Order* bombOrder = new Bomb(strategyExecuter, terrToBomb);
                    strategyExecuter->getOrderList()->add(bombOrder);
                    strategyExecuter->getPlayerHand()->play(2, Player::common_deck);
                    orderCreated = true;
                    return orderCreated;
                }
                else if (card->get_type() == 3) {
                    //very dumb for player to create blockade on such territory.
                    Order* blockadeOrder = new Blockade(strategyExecuter, strongestTerritory);
                    strategyExecuter->getOrderList()->add(blockadeOrder);
                    strategyExecuter->getPlayerHand()->play(3, Player::common_deck);
                    orderCreated = true;
                    return orderCreated;
                }
                else if (card->get_type() == 4) {
                    Player* playerToNegotiateWith;
                    for (int i = 0; i < territoriesToAttack.size(); i++) {
                        if (territoriesToAttack[i]->getTerritoryOccupant() != NULL) {
                            playerToNegotiateWith = territoriesToAttack[i]->getTerritoryOccupant();
                            Order* negotiateOrder = new Negotiate(strategyExecuter, playerToNegotiateWith);
                            strategyExecuter->getOrderList()->add(negotiateOrder);
                            strategyExecuter->getPlayerHand()->play(4, Player::common_deck);
                            orderCreated = true;
                            return orderCreated;
                        }
                    }
                }
                else if (card->get_type() == 5) {
                    Order* reinforcementOrder = new Reinforcement(strategyExecuter);
                    strategyExecuter->getOrderList()->add(reinforcementOrder);
                    strategyExecuter->getPlayerHand()->play(5, Player::common_deck);
                    orderCreated = true;
                    return orderCreated;
                }
                else { continue; }

            }
        }
        return orderCreated;
    }
}

vector<Territory*> AggressivePlayerStrategy::toDefend()
{

    vector<Territory*> territoryToBeDefended;
    for (int i = 0; i < strategyExecuter->getPlayerTerritories().size(); i++) {
        territoryToBeDefended.push_back(strategyExecuter->getPlayerTerritories()[i]);
    }


    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);


    return territoryToBeDefended;
}


vector<Territory*> AggressivePlayerStrategy::toAttack()
{

    vector<Territory*> vec;
    return  vec;


    //Build a vector of source territory attacking a target territory
    vector<Territory*> attackableTerritories;
    vector<Territory*> allTerritories = strategyExecuter->allTerritoryVectorBuilder(strategyExecuter->getPlayerTerritories()[0]);
    //Remove territories that already belong to the players from the appropriate vector
    for (int i = 0; i < allTerritories.size(); i++) {
        bool isEnnemyTerritory = true;
        for (int j = 0; j < strategyExecuter->getPlayerTerritories().size(); j++) {
            if (allTerritories[i]->getTerritoryID() == strategyExecuter->getPlayerTerritories()[j]->getTerritoryID())
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

HumanPlayerStrategy::HumanPlayerStrategy(Player* executer)
{
    this->strategyExecuter = executer;
    cout << endl << "HUMAN PLAYER STRATEGY CREATED" << endl;
}

void HumanPlayerStrategy::issueOrder()
{

    vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR HUMANPLAYERSTRATEGY PLAYERS" << endl;
    for (int i = 0; i < toDefendTerr.size(); i++) {
        cout << *toDefendTerr[i] << endl;
    }

    cout << endl << "Human issue order called" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;

    for (int i = 0; i < strategyExecuter->getPlayerTerritories().size(); i++) {
        territoryToBeDefended.push_back(strategyExecuter->getPlayerTerritories()[i]);
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);


    return territoryToBeDefended;
}

vector<Territory*> HumanPlayerStrategy::toAttack()
{
    vector<Territory*> vec;
    return  vec;
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* executer)
{
    this->strategyExecuter = executer;
    cout << endl << "BENEVOLENT PLAYER STRATEGY CREATED" << endl;

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& obj) {
    *this = obj;
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& obj) {
    this->strategyExecuter = obj.strategyExecuter;
    return *this;
}
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
    cout << endl << "Benevolant strategy object destroyed" << endl;
}

void BenevolentPlayerStrategy::issueOrder()
{
    cout << endl << "===============================" << endl;
    cout << endl << " BENEVOLANT ISSUE ORDER CALLED " << endl;
    cout << endl << "===============================" << endl;
    //  this->strategyExecuter->getArmyToBePlaced();
    vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR BENEVOLENT PLAYERS" << endl;
    for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
        cout << *playerTerritoriesToDefend[i] << endl;
    }

    bool deployCreated = false;
    bool advanceCreated = false;
    // this->strategyExecuter->toAttack();
    if (this->strategyExecuter->getArmyToBePlaced() != 0) {


        //IMPLEMENTATION STARTS HERE
        sort(playerTerritoriesToDefend.begin(), playerTerritoriesToDefend.end(), Territory::compByincomingArmies);
        int numWeakTerrs = playerTerritoriesToDefend.size() / 2;
        int pool = this->strategyExecuter->getArmyToBePlaced();
        int armiesPerTerr = pool / numWeakTerrs;

        if (pool == 1) {
            cout << endl << "POOL EQUALS 1" << endl;
            Deploy* d = new Deploy(pool, playerTerritoriesToDefend[0], strategyExecuter);
            deployCreated = true;
            playerTerritoriesToDefend[0]->incomingArmies = armiesPerTerr + playerTerritoriesToDefend[0]->getNumArmies();
            //playerTerritoriesToDefend[0]->addNumArmies(pool);
            strategyExecuter->setArmyToBePlaced(0);
            strategyExecuter->getOrderList()->add(d);
            pool = 0;
        }
        else {


            Deploy* d = new Deploy(armiesPerTerr, playerTerritoriesToDefend[0], strategyExecuter);
            deployCreated = true;
            playerTerritoriesToDefend[0]->incomingArmies = armiesPerTerr + playerTerritoriesToDefend[0]->getNumArmies();
            //playerTerritoriesToDefend[0]->addNumArmies(armiesPerTerr);
            pool -= armiesPerTerr;

            strategyExecuter->getOrderList()->add(d);


            strategyExecuter->setArmyToBePlaced(pool);
            cout << endl << "POOL: " << pool << endl;
            cout << endl << "POOLTERR: " << armiesPerTerr << endl;
            cout << endl << "WEAKTERR: " << numWeakTerrs << endl;
            cout << endl << "VECTORSIZE: " << playerTerritoriesToDefend.size() << endl;
        }

        cout << endl << "AFTER BENEVOLANT DEPLOY" << endl;
        for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
            cout << *playerTerritoriesToDefend[i] << endl;
        }
        cout << endl << "===============================" << endl;
        cout << endl << " BENEVOLANT ISSUE ORDER DONE " << endl;
        cout << endl << "===============================" << endl;
    }

    else if(!deployCreated){
        cout << endl << "GOINT INTO THE ELSE" << endl;
       /* Commit* commit = new Commit();
        strategyExecuter->getOrderList()->add(commit);*/

        // Advance troop to weaker territories
        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
        sort(playerTerritoriesToDefend.begin(), playerTerritoriesToDefend.end(), Territory::compByincomingArmies);
        vector<Territory*> adjacentTerritories = playerTerritoriesToDefend[0]->getAdjacentTerritories();
        vector<Territory*> adjacentTerritoriesOfPlayer = strategyExecuter->getAdjacentTerritoriesOfPlayer(playerTerritoriesToDefend[0]);

        for (int i = 0; i < adjacentTerritoriesOfPlayer.size(); i++) {
            Territory* adjTerritory = adjacentTerritoriesOfPlayer[i];
            if (adjTerritory->getNonCommitedArmies() > 1) {

                //move half of the armies in the adjacent territories into the weakest territory
                int armiesToMove = adjTerritory->getNonCommitedArmies() / 2;

                cout << endl << "Benevolant player moving " << armiesToMove << " armies from " << adjTerritory->getName() << " to " << playerTerritoriesToDefend[0]->getName() << endl;
                Order* advanceOrder = new Advance(armiesToMove, adjTerritory, playerTerritoriesToDefend[0], strategyExecuter);
                advanceCreated = true;
                strategyExecuter->getOrderList()->add(advanceOrder);
                adjTerritory->decNonCommitedArmies(armiesToMove);


            }
        }
    }

    else if(!advanceCreated && !deployCreated){
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
    }
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;

    for (int i = 0; i < strategyExecuter->getPlayerTerritories().size(); i++) {
        territoryToBeDefended.push_back(strategyExecuter->getPlayerTerritories()[i]);
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);

    return territoryToBeDefended;
}

vector<Territory*> BenevolentPlayerStrategy::toAttack()
{
    vector<Territory*> vec;
    return  vec;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* executer)
{
    this->strategyExecuter = executer;
    cout << endl << "NEUTRAL PLAYER STRATEGY CREATED" << endl;
}

void NeutralPlayerStrategy::issueOrder()
{

    vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR NEUTRAL PLAYERS" << endl;
    for (int i = 0; i < toDefendTerr.size(); i++) {
        cout << *toDefendTerr[i] << endl;
    }
    cout << endl << "Neutral issue order called" << endl;


    //the requirement is that the neutral player does not issue any order. for that reason, the neutral player remains with only 0 armies on
    //the territories he owns since he can't even issue deploy orders
    strategyExecuter->setArmyToBePlaced(0);
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);


}

vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;

    for (int i = 0; i < strategyExecuter->getPlayerTerritories().size(); i++) {
        territoryToBeDefended.push_back(strategyExecuter->getPlayerTerritories()[i]);
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);


    return territoryToBeDefended;
}

vector<Territory*> NeutralPlayerStrategy::toAttack()
{

    //for the time being , the neutral territory does not attack and therefore this function serves only as a place holder
    vector<Territory*> vec;
    return  vec;
}
