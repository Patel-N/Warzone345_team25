
#include "Player.h"
#include "Map.h"
#include<iostream>
#include<windows.h>
//using namespace std;
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
    this->strategyExecuter = executer;// this is just the player object currently using his strategy
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
        token = s.substr(0, pos+1);
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
                cout << "card ID : "<<i <<" : "<< cardTypeString << endl;
            }
            cout << "please enter the ID of the cards you wish to play using this format: 2,3,5,1"<<endl;
            
             cin >> UserInput;
             if (UserInput.compare("no card") != 0) {
                 std::string s = UserInput;//this chunck parses UserInput input
                 std::string delimiter = ",";
                 size_t pos = 0;
                 std::string token;
                 vector<int> parseInput ;
                 while ((pos = s.find(delimiter)) != std::string::npos) {
                     
                     token = s.substr(0, pos);
                     parseInput.push_back( stoi(token));
                     s.erase(0, pos + delimiter.length());
                 }        
                 parseInput.push_back(stoi(s));


                 for (int i = 0; i < parseInput.size(); i++) {//for the size of user input
                     int type =strategyExecuter->getPlayerHand()->getCardsInHand().at(parseInput.at(i))->get_type();

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
                           Order* DiplomacyOrder = new Negotiate(strategyExecuter,currentPlayerTerritoryPointer1.at(i)->getTerritoryOccupant());
                           strategyExecuter->getOrderList()->add(DiplomacyOrder);
                           //removing card from hand
                           strategyExecuter->getPlayerHand()->play(4, Player::common_deck);
                     }
                     if (type == 5) {
                         cout << "REINFORCEMENT CARD" << endl;
   
                         Player *tempPointer = strategyExecuter;
                         Order* ReinforcementOrder = new Reinforcement(strategyExecuter);
                         strategyExecuter->getOrderList()->add(ReinforcementOrder);
                         //removing card from hand
                         strategyExecuter->getPlayerHand()->play(5, Player::common_deck);
                     }


                   
                 }
             
                 
             }
            

        }
    }

   //move troops (attack/defend) step ------------------------------
    cout << endl<< "-Hello " << strategyExecuter->getPlayerName() << "!-" << endl;
    cout << "Do you wish to move your troops to another territory? yes/no" << endl;
    cout << "if you type yes, will display your territories and territories next to them." << endl << endl;
    cin >> UserInput;
    cout << endl;
    if (UserInput.compare("yes") == 0) {//if user wants to move troops, display mini UI
                                        // mini UI works in 3 steps, 1.display his current territory, 2.display enemy territories user can attack, 3. prompt user and move troops
        cout << "-----------------------you own territories: -------------------------------"<< endl << endl;
        vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
        for (int i = 0; i < toDefendTerr.size(); i++) {// 1.display all territory user has
            cout << *toDefendTerr[i];
            vector<Territory*>tempADJTerritory = toDefendTerr[i]->getAdjacentTerritories();
            cout << "adjacent territory ID:";
            for (int j = 0; j < tempADJTerritory.size(); j++) {
                cout << tempADJTerritory.at(j)->getTerritoryID()<<",";
            }
            cout << endl<<endl;
            Sleep(100);
        }
        cout << "to show enemy territories info that can be attacked this turn type: show" << endl << endl;
        cin >> UserInput;
        if (UserInput.compare("show") == 0){//2.display enemy territory user can attack
            cout << "-------------here is the information of the territories you can attack/defend:--------------------" << endl << endl;
            vector<Territory*> territoriesAvailableToBeAttacked = this->strategyExecuter->toAttack();
            for (int i = 0; i < territoriesAvailableToBeAttacked.size(); i++) {// 1.display all territory to  available to attack
                cout << *territoriesAvailableToBeAttacked[i] ;
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
        cout <<endl<<endl<< "Now please indicate where do you want to move your armies using ID's" << endl;
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
    cout <<endl<< "this is the end of your turn, press any key to continue, Goodluck " << strategyExecuter->getPlayerName()<<"!!!"<< endl;
    cin >> UserInput;
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

