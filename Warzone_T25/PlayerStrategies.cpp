
#include "Player.h"
#include "Map.h"
#include<iostream>
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* executer) {
    this->strategyExecuter = executer;
    cout << endl << "AGGRESSIVE PLAYER STRATEGY CREATED" << endl;
}

void AggressivePlayerStrategy::issueOrder() {
    cout << endl << "Aggressive issue order called" << endl;
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
    cout << endl << "STRONGEST TERRITORY BEFORE DEPLOYEMENT" << endl;
    cout << *strongestTerritory << endl;
    bool deployOrderCreated, moveFromFriendlyOrderCreated;
    deployOrderCreated = deployStrategy(strongestTerritory);//argument = strongest territory
    cout << endl << "VALUE OF DEPLOY " << deployOrderCreated << endl;
      //the player only get to this stage once all armies have been deployed
      //AGGRESSIVE PLAYER strategy:
      //1: verify if the strongest territory can be reinforced with other adjacent friendly territory. if yes create advance orders
      //2: verify if there is an airlift option, if yes, see if strongest territory can be reinforced with other friendly territories if yes, create airlift orders
    if (!deployOrderCreated) {
        moveFromFriendlyOrderCreated = movingFriendlyTroopsAroundStrategy(strongestTerritory);
        if (!moveFromFriendlyOrderCreated) {
            //bool attackOrderCreated = attackStrategy(strongestTerritory);
        }
    }
    if (!deployOrderCreated && !moveFromFriendlyOrderCreated) {
        Commit* commit = new Commit();
        strategyExecuter->getOrderList()->add(commit);
    }

}

bool AggressivePlayerStrategy::deployStrategy(Territory* strongestTerritory) {
    // Everytime issue order is called, we verify if a deploy order can still be issued
    bool orderCreated = false;
    if (this->strategyExecuter->getArmyToBePlaced() != 0) {
        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
        //the aggressive player would want to advance on its stronger territory
        cout << endl << "TERRITORIES TO DEFEND FOR AGGRESSIVE PLAYERS" << endl;
        for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
            cout << *playerTerritoriesToDefend[i] << endl;
        }
                
        Deploy* d = new Deploy(this->strategyExecuter->getArmyToBePlaced(), strongestTerritory, strategyExecuter);
        strategyExecuter->getOrderList()->add(d);
        strategyExecuter->addToArmiesToBePlaced(-this->strategyExecuter->getArmyToBePlaced());
        orderCreated = true;
        cout << endl << "AFTER DEPLOY" << endl;
        for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
            cout << *playerTerritoriesToDefend[i] << endl;
        }
        return orderCreated;       
    }
    else {
        return orderCreated;
    }
}

bool AggressivePlayerStrategy::movingFriendlyTroopsAroundStrategy(Territory* strongestTerritory) {
    vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    vector<Territory*> adjacentTerritories = strongestTerritory->getAdjacentTerritories();
    vector<Territory*> adjacentTerritoriesOfPlayer = strategyExecuter->getAdjacentTerritoriesOfPlayer(strongestTerritory);
    vector<Territory*> nonAdjacentTerritoriesOfPlayer = strategyExecuter->getNonAdjacentTerritoriesOfPlayer(strongestTerritory);
    bool orderCreated = false;
    cout << endl << "ADJACENT TERRITORIES" << endl;
    for (int i = 0; i < adjacentTerritoriesOfPlayer.size(); i++) {
        Territory* adjTerritory = adjacentTerritoriesOfPlayer[i];
        if (adjTerritory->getNonCommitedArmies() > 1) {
            //we leave one army behind, and move the rest to the strongest territory by creating an advance order
            int armiesToMove = adjTerritory->getNonCommitedArmies() - 1;
            if (!orderCreated) {
                cout << endl << "NON COMMITTED ARMIES OF ADJ " << adjTerritory->getNonCommitedArmies() << endl;
                Order* advanceOrder = new Advance(armiesToMove, adjTerritory, strongestTerritory, strategyExecuter);
                strategyExecuter->getOrderList()->add(advanceOrder);
                adjTerritory->decNonCommitedArmies(armiesToMove);
                cout << endl << "RETURNING TRUE" << endl;
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
                    Order* airliftOrder = new Airlift(armiesToAirlift, friendlyTerritoryThatRequiresAirlift, strongestTerritory, strategyExecuter);
                    strategyExecuter->getOrderList()->add(airliftOrder);
                    friendlyTerritoryThatRequiresAirlift->decNonCommitedArmies(armiesToAirlift);
                    //removing card from hand
                    strategyExecuter->getPlayerHand()->play(1, Player::common_deck);
                    cout << endl << "RETURNING TRUE AIRLIFT" << endl;
                    orderCreated = true;
                    return orderCreated;
                }
            }
        }
    }
    cout << endl << "ADJACENT TERRITORIES OF PLAYER" << endl;
    for (int i = 0; i < adjacentTerritoriesOfPlayer.size(); i++) {
        cout << endl << *adjacentTerritoriesOfPlayer[i] << endl;
    }
    cout << endl << "NON ADJACENT TERRITORY OF PLAYER" << endl;
    for (int i = 0; i < nonAdjacentTerritoriesOfPlayer.size(); i++) {
        cout << endl << *nonAdjacentTerritoriesOfPlayer[i] << endl;
    }
    return false;
}

bool AggressivePlayerStrategy::attackStrategy(Territory*) {
    return true;
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

void BenevolentPlayerStrategy::issueOrder()
{
    vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR BENEVOLENT PLAYERS" << endl;
    for (int i = 0; i < toDefendTerr.size(); i++) {
        cout << *toDefendTerr[i] << endl;
    }
    cout << endl << "Benevolent issue order called" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
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
    vector<Territory*> vec;
    return  vec;
}
