
#include "Player.h"
#include "Map.h"
#include<iostream>
#include<windows.h>
//using namespace std;
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* executer) {
    this->strategyExecuter = executer;
    cout << endl << "AGGRESSIVE PLAYER STRATEGY CREATED" << endl;
}
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& obj) {
    *this = obj;
}



AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& obj) {
    this->strategyExecuter = obj.strategyExecuter;
    return *this;
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
            cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " not able to move troops around" << endl;
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
        cout << endl << " Available armies in pool: " << this->strategyExecuter->getArmyToBePlaced() << endl;
        cout << endl << " Deploying " << this->strategyExecuter->getArmyToBePlaced() << " on strongest territory " << strongestTerritory->getName() << " ID# " << strongestTerritory->getTerritoryID() << endl;
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

            cout << endl << "Aggressive Player " << strategyExecuter->getPlayerName() << " About to issue attack order..." << endl;
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
    this->strategyExecuter = executer;// this is just the player object currently using his strategy
    cout << endl << "HUMAN PLAYER STRATEGY CREATED" << endl;
}


void HumanPlayerStrategy::issueOrder() {
    // this function is in 4 steps: deploy army, play cards, move troops (attack/defend). marked with --------
    // for every of these steps the user will get prompted and will insert a value
    // at the end of function commit object is added to order list, indicating that player has finish issuing orders

    if (strategyExecuter->getIsCommited() == true) {// if the player has already commited, dont even go through the code
        return;
    }
    string UserInput;// variable used to store user input

    bool hasDeployed=false;// these bools is for the round robin for each of the 3 steps.
    bool hasPlayedCard=false;
    bool hasMovedTroops=false;

    if (strategyExecuter->getArmyToBePlaced() == 0) {//this says, if player does not have army to deploy, then he deployed already
        hasDeployed = true;
    }
    if (hasDeployed == false) {
        //deploy army step------------------------------
        cout << endl << "---Hello " << strategyExecuter->getPlayerName() << "!---" << endl;
        cout << "where do you wish to deploy your armies?" << endl;

        cout << "here are the territories you currently own:" << endl << endl;

        vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
        for (int i = 0; i < toDefendTerr.size(); i++) {// display all territory user has
            cout << *toDefendTerr[i] << endl;
        }

        cout << "you have : * " << strategyExecuter->getArmyToBePlaced() << " * armies to place" << endl;
        cout << "to deploy your army, use the following format: (1,2),(5,6),(10,3)" << endl;
        cout << "meaning: place 1 army to territory of ID 2, 5 army to territory of ID 6, and 10 army to territory ID 3" << endl;
        cin >> UserInput;
        //parsing userInput and placing armies
        std::string s = UserInput;//temp variables for parsin
        std::string delimiter = "),";
        size_t pos = 0;
        vector<string> vectorOfUserInput;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos + 1);
            vectorOfUserInput.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        vectorOfUserInput.push_back(s);//user input parsed into this vector

        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();// list of players current territories
        for (int i = 0; i < vectorOfUserInput.size(); i++) {// for the size of the user input/size of vector parsed input
            int armyToBePlaced = 0;//num army player wants to place
            int territoryIDUserInput = 0;//ID player input
            Territory* territoryPointer = NULL;//the pointer to the actual territory player wants to deploy army to

            std::string s = vectorOfUserInput.at(i);//this chunck parses (armyToBePlaced,territoryIDUserInput) input
            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(1, pos);
                armyToBePlaced = stoi(token);
                s.erase(0, pos + delimiter.length());
            }
            territoryIDUserInput = stoi(s);

            for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {//this chunck looks for the territory by ID
                if (playerTerritoriesToDefend.at(i)->getTerritoryID() == territoryIDUserInput) {
                    territoryPointer = playerTerritoriesToDefend.at(i);
                    break;
                }
            }
            Deploy* d = new Deploy(armyToBePlaced, territoryPointer, strategyExecuter);//sets order depending of user input
            strategyExecuter->getOrderList()->add(d);// add to the list of orders of the player
            cout << "you ordered : " << armyToBePlaced << " armie(s) to territory ID: " << territoryIDUserInput << endl;
        }
        cout << "army deployment sucessfull!" << endl;
        strategyExecuter->addToArmiesToBePlaced(-this->strategyExecuter->getArmyToBePlaced());//sets army to be placed to 0
    }
    if ((hasDeployed == true)&(strategyExecuter->getIsCardPlayed()==false)) {
        //play card step------------------------------
        if (strategyExecuter->getPlayerHand()->getCardsInHand().size() > 0) {// if player has atleast a card prompt him

            cout << endl << "--Hello " << strategyExecuter->getPlayerName() << "--!" << endl;
            cout << "Do you wish to play one of your cards? yes/no" << endl;
            cin >> UserInput;
            if (UserInput.compare("yes") == 0) {// if player wants to play cards, display his cards 
                cout << "here are the cards you currently have:" << endl << endl;;
                for (int i = 0; i < strategyExecuter->getPlayerHand()->getCardsInHand().size(); i++) {//displaying cards
                    int cardTypeINT = 0;// card types are in int, so displaying into string so the player can understand better, maybe wil be implemented in cards.cpp instead
                    string cardTypeString = "";
                    cardTypeINT = strategyExecuter->getPlayerHand()->getCardsInHand().at(i)->get_type();
                    switch (cardTypeINT) {
                    case 1: cardTypeString = "AIRLIFT CARD";
                        break;
                    case 2: cardTypeString = "BOMB CARD";
                        break;
                    case 3: cardTypeString = "BLOCKADE CARD";
                        break;
                    case 4: cardTypeString = "DIPLOMACY CARD";
                        break;
                    case 5: cardTypeString = "REINFORCEMENT CARD";
                        break;
                    }
                    cout << "card ID : " << i << " : " << cardTypeString << endl;
                }
                cout << "please enter the ID of the cards you wish to play using this format: 2,3,5,1" << endl;

                cin >> UserInput;
                if (UserInput.compare("no card") != 0) {
                    std::string s = UserInput;//this chunck parses UserInput input
                    std::string delimiter = ",";
                    size_t pos = 0;
                    std::string token;
                    vector<int> parseInput;
                    while ((pos = s.find(delimiter)) != std::string::npos) {

                        token = s.substr(0, pos);
                        parseInput.push_back(stoi(token));
                        s.erase(0, pos + delimiter.length());
                    }
                    parseInput.push_back(stoi(s));


                    for (int i = 0; i < parseInput.size(); i++) {//for the size of user input
                        int type = strategyExecuter->getPlayerHand()->getCardsInHand().at(parseInput.at(i))->get_type();

                        if (type == 1) {
                            cout << "AIRLIFT CARD" << endl;
                            int armiesToAirlift = 0;
                            int friendlyTerritoryThatRequiresAirlift = 0;
                            int targetTerritory = 0;
                            Territory* friendlyTerritoryThatRequiresAirliftPointer = NULL;
                            Territory* targetTerritoryPointer = NULL;
                            cout << "enter number of armies you need lifting" << endl;
                            cin >> armiesToAirlift;
                            cout << "enter number ID of territory that you airlift from" << endl;
                            cin >> friendlyTerritoryThatRequiresAirlift;
                            cout << "enter number ID of target territory" << endl;
                            cin >> targetTerritory;
                            cout << endl;
                            vector<Territory*>  currentPlayerTerritoryPointer1 = this->strategyExecuter->toDefend();// list of players current territories
                            for (int i = 0; i < currentPlayerTerritoryPointer1.size(); i++) {//this  looks for the territory by ID
                                if (currentPlayerTerritoryPointer1.at(i)->getTerritoryID() == friendlyTerritoryThatRequiresAirlift) {
                                    friendlyTerritoryThatRequiresAirliftPointer = currentPlayerTerritoryPointer1.at(i);
                                    break;
                                }
                            }
                            for (int i = 0; i < currentPlayerTerritoryPointer1.size(); i++) {//this chunck looks for the territory by ID
                                if (currentPlayerTerritoryPointer1.at(i)->getTerritoryID() == targetTerritory) {//this  looks for the territory by ID
                                    targetTerritoryPointer = currentPlayerTerritoryPointer1.at(i);
                                    break;
                                }
                            }

                            Order* airliftOrder = new Airlift(armiesToAirlift, friendlyTerritoryThatRequiresAirliftPointer, targetTerritoryPointer, strategyExecuter);
                            strategyExecuter->getOrderList()->add(airliftOrder);
                            //removing card from hand
                            strategyExecuter->getPlayerHand()->play(1, Player::common_deck);
                        }
                        if (type == 2) {
                            cout << "BOMB CARD" << endl;
                            vector<Territory*>  currentPlayerTerritoryPointer1 = this->strategyExecuter->toAttack();// list of players current territories
                            for (int j = 0; j < currentPlayerTerritoryPointer1.size(); j++) {

                            }

                            int territoryToBomb = NULL;
                            Territory* territoryToBombPOINTER = NULL;
                            cout << "enter territoryID to bomb" << endl;
                            cin >> territoryToBomb;

                            for (int i = 0; i < currentPlayerTerritoryPointer1.size(); i++) {//this  looks for the territory by ID
                                if (currentPlayerTerritoryPointer1.at(i)->getTerritoryID() == territoryToBomb) {
                                    territoryToBombPOINTER = currentPlayerTerritoryPointer1.at(i);
                                    break;
                                }
                            }

                            Order* BombOrder = new Bomb(strategyExecuter, territoryToBombPOINTER);
                            strategyExecuter->getOrderList()->add(BombOrder);
                            //removing card from hand
                            strategyExecuter->getPlayerHand()->play(2, Player::common_deck);
                        }
                        if (type == 3) {
                            cout << "BLOCKADE CARD" << endl;
                            int targetTerritory = 0;
                            Territory* targetTerritoryPointer = NULL;
                            cout << "enter territoryID to blockade" << endl;
                            cin >> targetTerritory;
                            cout << endl;
                            vector<Territory*>  currentPlayerTerritoryPointer1 = this->strategyExecuter->toDefend();// list of players current territories
                            for (int i = 0; i < currentPlayerTerritoryPointer1.size(); i++) {//this chunck looks for the territory by ID
                                if (currentPlayerTerritoryPointer1.at(i)->getTerritoryID() == targetTerritory) {//this  looks for the territory by ID
                                    targetTerritoryPointer = currentPlayerTerritoryPointer1.at(i);
                                    break;
                                }
                            }

                            Order* blockadeOrder = new Blockade(strategyExecuter, targetTerritoryPointer);
                            strategyExecuter->getOrderList()->add(blockadeOrder);
                            //removing card from hand
                            strategyExecuter->getPlayerHand()->play(3, Player::common_deck);
                        }
                        if (type == 4) {
                            cout << "DIPLOMACY CARD" << endl;
                            int playerIDtonegociate = 0;
                            Player* playerIDtonegociatePointer = NULL;
                            cout << "enter the playerID of the player you wish to negociate with" << endl;
                            cin >> playerIDtonegociate;
                            vector<Territory*>  currentPlayerTerritoryPointer1 = this->strategyExecuter->toAttack();// list of players current territories
                            for (int i = 0; i < currentPlayerTerritoryPointer1.size(); i++) {//this chunck looks for the territory by ID
                                if (currentPlayerTerritoryPointer1.at(i)->getTerritoryOccupant()->getPlayerId() == playerIDtonegociate) {//this  looks for the territory by ID
                                    playerIDtonegociatePointer = currentPlayerTerritoryPointer1.at(i)->getTerritoryOccupant();
                                    break;
                                }
                            }
                            Order* DiplomacyOrder = new Negotiate(strategyExecuter, currentPlayerTerritoryPointer1.at(i)->getTerritoryOccupant());
                            strategyExecuter->getOrderList()->add(DiplomacyOrder);
                            //removing card from hand
                            strategyExecuter->getPlayerHand()->play(4, Player::common_deck);
                        }
                        if (type == 5) {
                            cout << "REINFORCEMENT CARD" << endl;

                            Player* tempPointer = strategyExecuter;
                            Order* ReinforcementOrder = new Reinforcement(strategyExecuter);
                            strategyExecuter->getOrderList()->add(ReinforcementOrder);
                            //removing card from hand
                            strategyExecuter->getPlayerHand()->play(5, Player::common_deck);
                        }



                    }


                }


            }
           // else { strategyExecuter->setIsCardPlayed(true); }// this says: the player has played a card, the engin will not prompt the player this turn to play cards anymore, if player says dosent want to play cards
        }
        strategyExecuter->setIsCardPlayed(true);// this says: the player has played a card, the engin will not prompt the player this turn to play cards anymore
    }

    if ((hasDeployed == true) & (strategyExecuter->getIsCardPlayed() == true) & (strategyExecuter->getAttackApplied() == false)) {
        //move troops (attack/defend) step ------------------------------
        cout << endl << "-Hello " << strategyExecuter->getPlayerName() << "!-" << endl;
        cout << "Do you wish to move your troops to another territory? yes/no" << endl;
        cout << "if you type yes, will display your territories and territories next to them." << endl << endl;
        cin >> UserInput;
        cout << endl;
        if (UserInput.compare("yes") == 0) {//if user wants to move troops, display mini UI
                                            // mini UI works in 3 steps, 1.display his current territory, 2.display enemy territories user can attack, 3. prompt user and move troops
            cout << "-----------------------you own territories: -------------------------------" << endl << endl;
            vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
            for (int i = 0; i < toDefendTerr.size(); i++) {// 1.display all territory user has
                cout << *toDefendTerr[i];
                vector<Territory*>tempADJTerritory = toDefendTerr[i]->getAdjacentTerritories();
                cout << "adjacent territory ID:";
                for (int j = 0; j < tempADJTerritory.size(); j++) {
                    cout << tempADJTerritory.at(j)->getTerritoryID() << ",";
                }
                cout << endl << endl;
                Sleep(100);
            }
            cout << "to show enemy territories info that can be attacked this turn type: show" << endl << endl;
            cin >> UserInput;
            if (UserInput.compare("show") == 0) {//2.display enemy territory user can attack
                cout << "-------------here is the information of the territories you can attack/defend:--------------------" << endl << endl;
                vector<Territory*> territoriesAvailableToBeAttacked = this->strategyExecuter->toAttack();
                for (int i = 0; i < territoriesAvailableToBeAttacked.size(); i++) {// 1.display all territory to  available to attack
                    cout << *territoriesAvailableToBeAttacked[i];
                    vector<Territory*>tempADJTerritory = territoriesAvailableToBeAttacked[i]->getAdjacentTerritories();
                    cout << "adjacent territory ID:";
                    for (int j = 0; j < tempADJTerritory.size(); j++) {
                        cout << tempADJTerritory.at(j)->getTerritoryID() << ",";
                    }
                    cout << endl << endl;
                    Sleep(70);
                }
            }
            //3.prompt user to show wich territory to attack, and parse the input and turn it into orders
            cout << endl << endl << "Now please indicate where do you want to move your armies using ID's" << endl;
            cout << "if you move armies into enemy territory, it will be considered as an attack!" << endl;
            cout << "to move armies, TYPE IN THE FOLLOWING FORMAT: (2,3,4),(8,5,10),(2,4,7)" << endl;
            cout << " example meaning: " << endl;
            cout << "move 2 armies from territory 3 to territory 4" << endl;
            cout << "move 8 armies from territory 5 to territory 10" << endl;
            cout << "move 2 armies from territory 4 to territory 7" << endl;
            cin >> UserInput;
            //parsing userInput and placing armies
            std::string s = UserInput;//temp variables for parsin
            std::string delimiter = "),";
            size_t pos = 0;
            vector<string> vectorOfUserInput;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos + 1);
                vectorOfUserInput.push_back(token);
                s.erase(0, pos + delimiter.length());
            }
            vectorOfUserInput.push_back(s);//user input parsed into this vector
            for (int i = 0; i < vectorOfUserInput.size(); i++) {
                int armyToMove = 0;//num army player wants to move
                int territoryIDfrom = 0;//ID player input
                int territoryIDto = 0;//ID player input2
                Territory* territoryPointerFROM = NULL;//the pointer to the actual territory player wants to move army from
                Territory* territoryPointerTO = NULL;//the pointer to the actual territory player wants to deploy army to

                std::string s = vectorOfUserInput.at(i).substr(1, vectorOfUserInput.at(i).size() - 2);//this chunck parses (1,2,5) input format     
                std::string delimiter = ",";
                size_t pos = 0;
                std::string token;
                while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);

                    armyToMove = stoi(token);
                    s.erase(0, pos + delimiter.length());

                    token = s.substr(0, pos);

                    territoryIDfrom = stoi(token);
                    s.erase(0, pos + delimiter.length());

                }
                territoryIDto = stoi(s);

                vector<Territory*> currentPlayerTerritoryPointer = this->strategyExecuter->toDefend();// list of players current territories
                for (int i = 0; i < currentPlayerTerritoryPointer.size(); i++) {//this chunck looks for the territory by ID
                    if (currentPlayerTerritoryPointer.at(i)->getTerritoryID() == territoryIDfrom) {
                        territoryPointerFROM = currentPlayerTerritoryPointer.at(i);
                        break;
                    }
                }
                vector<Territory*> searchTerritoryfromtoDefend = this->strategyExecuter->toDefend();// list of players current territories
                for (int i = 0; i < searchTerritoryfromtoDefend.size(); i++) {//this chunck looks for the territory by ID
                    if (searchTerritoryfromtoDefend.at(i)->getTerritoryID() == territoryIDto) {
                        territoryPointerTO = searchTerritoryfromtoDefend.at(i);
                        break;
                    }
                }
                vector<Territory*> searchTerritoryfromtoAttack = this->strategyExecuter->toAttack();// list of players current territories
                for (int i = 0; i < searchTerritoryfromtoAttack.size(); i++) {//this chunck looks for the territory by ID
                    if (searchTerritoryfromtoAttack.at(i)->getTerritoryID() == territoryIDto) {
                        territoryPointerTO = searchTerritoryfromtoAttack.at(i);
                        break;
                    }
                }
                Order* advanceOrder = new Advance(armyToMove, territoryPointerFROM, territoryPointerTO, strategyExecuter);//advance order
                strategyExecuter->getOrderList()->add(advanceOrder);
                cout << "you sent " << armyToMove << " armie(s) from territoryID: " << territoryPointerFROM->getTerritoryID() << " to territoryID: " << territoryPointerTO->getTerritoryID() << endl;
            }
        }
        cout << endl << "this is the end of your turn, press any key to continue, Goodluck " << strategyExecuter->getPlayerName() << "!!!" << endl;
        strategyExecuter->setAttackApplied(true);// this says, ok the play has attacked/defended this turn, the game engin will not promp player anymore to attack/defend
        cin >> UserInput;
    }

    if ((hasDeployed == true) & (strategyExecuter->getIsCardPlayed() == true) & (strategyExecuter->getAttackApplied() == true)) {
        //commit, end of issue orders step------------------------------
        strategyExecuter->setIsCommited(true);//sets is commited true, getIsCardPlayed and getAttackApplied is resseted in the game engin every turn
        Commit* commit = new Commit();
        strategyExecuter->getOrderList()->add(commit);// when commited, user will not be prompted anymore to ussie order under next turn
    }

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

// Benevolant constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* executer)
{
    this->strategyExecuter = executer;
    cout << endl << "BENEVOLENT PLAYER STRATEGY CREATED" << endl;

}

// Benevolant copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& obj) {
    *this = obj;
}

// Beneolant assignment operator
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& obj) {
    this->strategyExecuter = obj.strategyExecuter;
    return *this;
}

// Benevolant Destructor
BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
    cout << endl << "Benevolant strategy object destroyed" << endl;
}

// Benevolant insetion stream operator
ostream& operator<<(ostream& outs, const BenevolentPlayerStrategy& theObject)
{
    outs << endl << "This player has an benevolant strategy" << endl;
    return outs;
}

// Benevolant IssurOrder
void BenevolentPlayerStrategy::issueOrder()
{
    cout << endl << "===============================" << endl;
    cout << endl << " BENEVOLANT ISSUE ORDER CALLED " << endl;
    cout << endl << "===============================" << endl;

    // Prints territories of current player
    vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR BENEVOLENT PLAYERS" << endl;
    for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
        cout << *playerTerritoriesToDefend[i] << endl;
    }


    bool deployCreated = false;
    bool advanceCreated = false;
    bool orderCreated = false;

    // If there are armies in the pool, sort territories and add to weakest territories. Each call sorts the vector
    // to keep track of weakest territory.
    if (this->strategyExecuter->getArmyToBePlaced() != 0) {


        sort(playerTerritoriesToDefend.begin(), playerTerritoriesToDefend.end(), Territory::compByincomingArmies);
        int numWeakTerrs = playerTerritoriesToDefend.size() / 2;
        int pool = this->strategyExecuter->getArmyToBePlaced();
        int armiesPerTerr = pool / numWeakTerrs;

        if (pool == 1 || pool < armiesPerTerr) {
            cout << endl << "POOL EQUALS 1" << endl;
            Deploy* d = new Deploy(pool, playerTerritoriesToDefend[0], strategyExecuter);
            deployCreated = true;
            playerTerritoriesToDefend[0]->incomingArmies = armiesPerTerr + playerTerritoriesToDefend[0]->getNumArmies();
            strategyExecuter->setArmyToBePlaced(0);
            strategyExecuter->getOrderList()->add(d);
            pool = 0;
        }

        else {


            Deploy* d = new Deploy(armiesPerTerr, playerTerritoriesToDefend[0], strategyExecuter);
            deployCreated = true;
            playerTerritoriesToDefend[0]->incomingArmies = armiesPerTerr + playerTerritoriesToDefend[0]->getNumArmies();
            pool -= armiesPerTerr;

            strategyExecuter->getOrderList()->add(d);


            strategyExecuter->setArmyToBePlaced(pool);
           
        }

    }

    // If no armies in pool continue to advance order.
    else if(!deployCreated){

        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
        sort(playerTerritoriesToDefend.begin(), playerTerritoriesToDefend.end(), Territory::compByincomingArmies);
        vector<Territory*> adjacentTerritories = playerTerritoriesToDefend[0]->getAdjacentTerritories();
        vector<Territory*> adjacentTerritoriesOfPlayer = strategyExecuter->getAdjacentTerritoriesOfPlayer(playerTerritoriesToDefend[0]);

        for (int i = 0; i < adjacentTerritoriesOfPlayer.size(); i++) {
            Territory* adjTerritory = adjacentTerritoriesOfPlayer[i];
            if (adjTerritory->getNonCommitedArmies() > 1) {

                // Move half of the armies in the adjacent territories into the weakest territory
                int armiesToMove = adjTerritory->getNonCommitedArmies() / 2;

                cout << endl << "Benevolant player moving " << armiesToMove << " armies from " << adjTerritory->getName() << " to " << playerTerritoriesToDefend[0]->getName() << endl;
                Order* advanceOrder = new Advance(armiesToMove, adjTerritory, playerTerritoriesToDefend[0], strategyExecuter);
                advanceCreated = true;
                strategyExecuter->getOrderList()->add(advanceOrder);
                adjTerritory->decNonCommitedArmies(armiesToMove);


            }
        }

        // If cards are available, attempt to play them using helper function.
        orderCreated = playCardsStrategy(playerTerritoriesToDefend[0]);
        if (orderCreated) { cout << endl << "Benevolant Player " << strategyExecuter->getPlayerName() << " successful at creating orders with cards" << endl; }
    }

    // If all orders are completed, commit.
    if(!advanceCreated && !deployCreated && !orderCreated){
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);
    }
        cout << endl << "===============================" << endl;
        cout << endl << " BENEVOLANT ISSUE ORDER DONE " << endl;
        cout << endl << "===============================" << endl;

}

// Returns vector of player territories.
vector<Territory*> BenevolentPlayerStrategy::toDefend()
{
    vector<Territory*> territoryToBeDefended;

    for (int i = 0; i < strategyExecuter->getPlayerTerritories().size(); i++) {
        territoryToBeDefended.push_back(strategyExecuter->getPlayerTerritories()[i]);
    }

    sort(territoryToBeDefended.begin(), territoryToBeDefended.end(), Territory::compByArmyCount);

    return territoryToBeDefended;
}

// Returns vector of enemy territories.
vector<Territory*> BenevolentPlayerStrategy::toAttack()
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

// Check each card in hand then plays it.
bool BenevolentPlayerStrategy::playCardsStrategy(Territory* weakestTerritory) {
    vector<Territory*> territoriesToAttack = strategyExecuter->toAttack();
    vector<Territory*> adjTerritoriesToAttack = strategyExecuter->getAdjacentTerritoriesToAttack(weakestTerritory);
    vector<Territory*> nonAdjacentTerritoriesToAttack = strategyExecuter->getNonAdjacentTerritoriesToAttack(weakestTerritory);
    bool orderCreated = false;
    if (strategyExecuter->getPlayerHand() != NULL) {
        Hand* playerHand = strategyExecuter->getPlayerHand();
        for (int i = 0; i < playerHand->getCardsInHand().size(); i++) {
            Card* card = playerHand->getCardsInHand()[i];
            if (card->get_type() == 1) { continue; }
            else {
                if (card->get_type() == 2) {
                    continue;
                }
                else if (card->get_type() == 3) {
                    //very dumb for player to create blockade on such territory.
                    Order* blockadeOrder = new Blockade(strategyExecuter, weakestTerritory);
                    strategyExecuter->getOrderList()->add(blockadeOrder);
                    strategyExecuter->getPlayerHand()->play(3, Player::common_deck);
                    orderCreated = true;
                    return orderCreated;
                }
                else if (card->get_type() == 4) {
                        cout << endl << "NEGIATE ATTACK VECTOR LOOP" << endl;
                        cout << endl << "TERRITORIES ATTACK SIZE" << territoriesToAttack.size() << endl;

                    Player* playerToNegotiateWith;
                    for (int i = 0; i < territoriesToAttack.size(); i++) {
                        if (territoriesToAttack[i]->getTerritoryOccupant() != NULL) {
                            playerToNegotiateWith = territoriesToAttack[i]->getTerritoryOccupant();
                            Order* negotiateOrder = new Negotiate(strategyExecuter, playerToNegotiateWith);
                            cout << endl << "NEGOTIATE ORDER CREATED" << endl;
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


NeutralPlayerStrategy::NeutralPlayerStrategy(Player* executer)
{
    this->strategyExecuter = executer;
    cout << endl << "NEUTRAL PLAYER STRATEGY CREATED" << endl;
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& obj)
{
    *this = obj;
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& obj)
{
    this->strategyExecuter = obj.strategyExecuter;
    return *this;
}

NeutralPlayerStrategy::~NeutralPlayerStrategy() {
    cout << endl << "Neutral strategy object destroyed" << endl;
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
    cout << endl << "neutral player does not issue any orders... Armies in pool have been removed for this turn" << endl;
    Commit* commit = new Commit();
    strategyExecuter->getOrderList()->add(commit);

    cout << endl << "===============================" << endl;
    cout << endl << "  NEUTRAL ISSUE ORDER DONE   " << endl;
    cout << endl << "===============================" << endl;

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


ostream& operator<<(ostream& outs, const AggressivePlayerStrategy& theObject)
{
    outs << endl << "This player has an aggressive strategy" << endl;
    return outs;
}

ostream& operator<<(ostream& outs, const NeutralPlayerStrategy& theObject)
{
    outs << endl << "This player has a neutral strategy" << endl;
    return outs;
}

