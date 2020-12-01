
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

void HumanPlayerStrategy::issueOrder() {
    // this function is in 4 steps: deploy army, play cards, move troops (attack/defend). marked with --------
    // for every of these steps the user will get prompted and will insert a value
    // at the end of function commit object is added to order list, indicating that player has finish issuing orders

    string UserInput;// variable used to store user input

    //deploy army step------------------------------
    cout << endl << "---Hello " << strategyExecuter->getPlayerName() << "!---" << endl;
    cout << "where do you wish to deploy your armies?" << endl;

    cout << "here are the territories you currently own:" << endl << endl;
    vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
    for (int i = 0; i < toDefendTerr.size(); i++) {// display all territory use has
        cout << *toDefendTerr[i] << endl;
    }
    cout << "you have : * " << strategyExecuter->getArmyToBePlaced() << " * armies to place" << endl;
    cout << "to deploy your army, use the following format: (1,2),(5,6),(10,3)" << endl;
    cout << "meaning: place 1 army to territory of ID 2, 5 army to territory of ID 6, and 10 army to territory ID 3" << endl;
    cin >> UserInput;
    // TODO : parsing userInput and placing armies


    //play card step------------------------------
    if (strategyExecuter->getPlayerHand()->getCardsInHand().size() > 0) {// if player has atleast a card prompt him
       
        cout << endl << "--Hello " << strategyExecuter->getPlayerName() << "--!" << endl;
        cout << "Do you wish to play one of your cards? yes/no" << endl;
        cin >> UserInput;
        if (UserInput.compare("yes") == 0) {// if player wants to play cards, display his cards 
            cout << "here are the cards you currently have:" << endl << endl;;
            for (int i = 0; i < strategyExecuter->getPlayerHand()->getCardsInHand().size(); i++) {//displaying cards
                int cardTypeINT=0;// card types are in int, so displaying into string so the player can understand better, maybe wil be implemented in cards.cpp instead
                string cardTypeString = "";
                cardTypeINT = strategyExecuter->getPlayerHand()->getCardsInHand().at(i)->get_type();
                switch (cardTypeINT) {
                case 1: cardTypeString = "AIRLIFT CARD";
                    break;
                case 2: cardTypeString = "BOMB CARD" ;
                    break;
                case 3: cardTypeString = "BLOCKADE CARD";
                    break;
                case 4: cardTypeString = "DIPLOMACY CARD";
                    break;
                case 5: cardTypeString = "REINFORCEMENT CARD";
                    break;
                }
                cout << "card ID:"<<i <<": "<< cardTypeString << endl;

            }
            cout << "please enter the ID of the card you wish to play"<<endl;
            cout << "if you wish to play no cards type: no card" << endl;
             cin >> UserInput;
            //TODO: card play for each type
        }
    }
   //move troops (attack/defend) step ------------------------------
    cout << "-Hello "<<strategyExecuter->getPlayerName()<<"!-" <<endl;
    cout << "Do you wish to move your troops to another territory? yes/no" << endl;



    if (UserInput.compare("yes") == 0) {


    }


    //commit, end of issue orders step------------------------------
    cout << endl << "Human issue order called" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);

}//end of void HumanPlayerStrategy::issueOrder() 

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

