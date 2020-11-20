
#include "Player.h"
#include "Map.h"
#include<iostream>
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* executer) {
    this->strategyExecuter = executer;
    cout << endl << "AGGRESSIVE PLAYER STRATEGY CREATED" << endl;
}

AggressivePlayerStrategy::~AggressivePlayerStrategy(){
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
    cout << endl << "strongest Territory Found... Here is the strongest territory of aggressive Player "<<strategyExecuter->getPlayerName() << endl;
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
               if(cardsPlayed){ cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " successful at creating orders with cards" << endl; }
               else{ cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " was not able to create orders with cards" << endl; }
           }
           else{ cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " succesffully issued attack orders" << endl; }
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
            cout << endl << "Available armies to attack with from strong territory: "<< strongestTerritory->getNonCommitedArmies()<<" armies " << endl;
            cout << endl << "Attacking with: "<< ArmiesToMarch <<" armies " << endl;
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
                if(card->get_type() == 2){
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
                else if (card->get_type() == 4){
                    Player* playerToNegotiateWith;
                    for (int i = 0; i < territoriesToAttack.size(); i++) {
                        if (territoriesToAttack[i]->getTerritoryOccupant() != NULL){
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
    cout << endl << "Human issue order called" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
}

vector<Territory*> HumanPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;

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
}

void BenevolentPlayerStrategy::issueOrder()
{
    cout << endl << "Benevolent issue order called" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
}

vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;
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
    //the requirement is that the neutral player does not issue any order. for that reason, the neutral player remains with only 0 armies on
    //the territories he owns since he can't even issue deploy orders
    strategyExecuter->setArmyToBePlaced(0);
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
    vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
    cout << endl << "Neutral issue order called" << endl;
}

vector<Territory*> NeutralPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;
    return territoryToBeDefended;
}

vector<Territory*> NeutralPlayerStrategy::toAttack()
{
    //for the time being , the neutral territory does not attack and therefore this function serves only as a place holder
    vector<Territory*> vec;
    return  vec;
}
