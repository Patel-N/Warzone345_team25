
#include "Player.h"
#include "Map.h"
#include<iostream>
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* executer) {
    this->strategyExecuter = executer;
    cout << endl << "AGGRESSIVE PLAYER STRATEGY CREATED" << endl;
}

void AggressivePlayerStrategy::issueOrder() {
    cout << endl << "Aggressive issue order called" << endl;
    //  this->strategyExecuter->getArmyToBePlaced();
      vector<Territory*> toDefendTerr = this->strategyExecuter->toDefend();
      cout << endl << "TERRITORIES TO DEFEND FOR AGGRESSIVE PLAYERS" << endl;
      for (int i = 0; i < toDefendTerr.size(); i++) {
          cout << *toDefendTerr[i] << endl;
      }
     // this->strategyExecuter->toAttack();
      if (this->strategyExecuter->getArmyToBePlaced() != 0) {

          vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();

          //the aggressive player would want to advance on its stronger territory
          int maxArmyTerritoryIndex = 0;
          int maxArmy = 0;
          for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
              if (playerTerritoriesToDefend[i]->getNumArmies() > maxArmy) {
                  maxArmy = playerTerritoriesToDefend[i]->getNumArmies();
                  maxArmyTerritoryIndex = i;
              }
          }
          Deploy* d = new Deploy(this->strategyExecuter->getArmyToBePlaced(), playerTerritoriesToDefend[maxArmyTerritoryIndex], strategyExecuter);
          strategyExecuter->getOrderList()->add(d);
          strategyExecuter->addToArmiesToBePlaced(-this->strategyExecuter->getArmyToBePlaced());
          cout << endl << "AFTER AGGRESSIVE DEPLOY" << endl;
          for (int i = 0; i < toDefendTerr.size(); i++) {
              cout << *toDefendTerr[i] << endl;
          }
      }    
      else {
          Commit* commit = new Commit();
          strategyExecuter->getOrderList()->add(commit);
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
    cout << endl << "Benevolent issue order called" << endl;
    //  this->strategyExecuter->getArmyToBePlaced();
        vector<Territory*> playerTerritoriesToDefend = this->strategyExecuter->toDefend();
    cout << endl << "TERRITORIES TO DEFEND FOR BENEVOLENT PLAYERS" << endl;
    for (int i = 0; i < playerTerritoriesToDefend.size(); i++) {
        cout << *playerTerritoriesToDefend[i] << endl;
    }
    // this->strategyExecuter->toAttack();
    if (this->strategyExecuter->getArmyToBePlaced() != 0) {


        //IMPLEMENTATION STARTS HERE
        sort(playerTerritoriesToDefend.begin(), playerTerritoriesToDefend.end(), Territory::compByincomingArmies);
        int numWeakTerrs = playerTerritoriesToDefend.size() / 2;
        int pool = this->strategyExecuter->getArmyToBePlaced();
        int armiesPerTerr = pool / numWeakTerrs;

        if (pool == 1) {
            Deploy* d = new Deploy(pool, playerTerritoriesToDefend[0], strategyExecuter);
            playerTerritoriesToDefend[0]->incomingArmies = armiesPerTerr + playerTerritoriesToDefend[0]->getNumArmies();
            //playerTerritoriesToDefend[0]->addNumArmies(pool);
            strategyExecuter->setArmyToBePlaced(0);
            strategyExecuter->getOrderList()->add(d);
            pool = 0;
        }
        else {

        
        Deploy* d = new Deploy(armiesPerTerr, playerTerritoriesToDefend[0], strategyExecuter);
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
    }

    else {
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
