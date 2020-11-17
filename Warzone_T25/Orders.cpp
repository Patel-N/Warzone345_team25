#pragma once
#include "Orders.h"
#include "Player.h"
#include "Map.h"



//Order
string Order::getorderName() {
	return this->orderName;
}

bool Order::getorderState() {
	return orderState;
}

void Order::setorderName(string name) {
	orderName = name;
}

void Order::setorderState(bool flag) {
	orderState = flag;
}

//Constructor 
Order::Order() {
	setorderName("order");
	setorderState(false);
}

Order::Order(const Order& order) {
	(*this).setorderState(order.orderState);
	(*this).setorderName(order.orderName);
}

//OverLoaded Assignment Operator
Order& Order::operator=(const Order& order) {
	(*this).setorderState(order.orderState);
	(*this).setorderName(order.orderName);
	return *this;
}

//Deploy
bool Deploy::validate() {
	cout << endl << "STEP1: verify that territory belongs to issuing player..." << endl;
	for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
		//step 1: validate that issuing player is deploying on friendly territory
		if (target->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
			cout << endl << "STEP1: SUCCESS.Proceeding to next step..." << endl;
			cout << endl << "STEP2: implicit step to verify if enough armies in player army pool" << endl;
			//implicit verrification to see if there are enough armies in pool
			if (armiesToDeploy > issuingPlayer->getArmyToBePlaced()) {
				cout << endl << "STEP2: FAIL... Attempt at deploying "<< armiesToDeploy <<" armies" << endl;
				cout << endl << "Avalable armies:  " << issuingPlayer->getArmyToBePlaced() << endl;
				return false;
			}
			cout << endl << "STEP2: SUCCESS... There are enough armies in the army pool" << endl;
			return true;
		}
	}
	cout << endl << "STEP1 FAIL. Territory does not belong to issuing player" << endl;
	return false;
}

void Deploy::execute(int playerIndex) {
	if (validate()) {
		cout <<endl<< "Validation Complete...Commencing execution for player "<<issuingPlayer->getPlayerId()<<" deploy order..." << endl;
		target->addNumArmies(armiesToDeploy);
		issuingPlayer->addToArmiesToBePlaced(-armiesToDeploy);
		setorderState(true); // Order Deploy is Executed
		cout << endl << "Armies have been deployed on territory " << target->getTerritoryID() << endl;
		cout << endl << "Here is the new Territory state: " << endl;
		cout << endl << *target << endl;
		cout << "================================" << endl;
	}
	else {
		setorderState(false); // Order Has not been executed- as couldnt be validated
		cout << endl << "Deploy order invalid. failed to execute" << endl;
	}
}

//Constructor 
Deploy::Deploy() {
	setorderName("deploy");
	setorderState(false);
}

Deploy::Deploy(int armies, Territory* target_t, Player* player) {
	setorderName("deploy");
	setorderState(false);
	armiesToDeploy = armies;
	target = target_t;
	issuingPlayer = player;
}

Deploy::~Deploy() {
}

Deploy::Deploy(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}

//OverLoaded Assignment Operator
Deploy& Deploy::operator=(Deploy& deploy) {
	if (this == &deploy) {
		return *this;
	}
	(*this).setorderState(deploy.getorderState());
	(*this).setorderName(deploy.getorderName());
	return *this;
}

// Advance
bool Advance::validate() {
	cout << endl << "Executing Player [ " << issuingPlayer->getPlayerId() << " ]" << "Advance order... Validate step 1: source belonging to issuing player..." << endl;
	//step 1: validate to make sure that source territory belongs to issuingPlayer
	if(issuingPlayer->getPlayerTerritories().size()>0){
		bool found = false;
		for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
			if ((source->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID())) {
				found = true;

			}
		}
		if (!found) { 
			cout << endl << "STEP 1 : FAIL. Territory does not belong to issuing player" << endl;
			return false; 
		}
	}
	cout << endl << "Step 1 SUCCESS. Proceeding to step 2..." << endl;
	//step 2: Validate if targeted territory is adjacent to advancing territory
	cout << endl << "Step2:Validating if target is adjacent.." << endl;
	if (this->source->getAdjacentTerritories().size()>0) {
		for (int i = 0; i < source->getAdjacentTerritories().size(); i++) {
			Territory* adjacent_terr = source->getAdjacentTerritories()[i];
			if (adjacent_terr->getTerritoryID() == target->getTerritoryID()) {
				cout << endl << "Targeted is Adjacent.   Time to March..." << endl;
				return true;
			}
		}
		cout << endl << "Targeted territory not Adjacent...Order is invalid" << endl;
		return false;
	}

	return false;	

}

void Advance::execute(int playerIndex) {
	if (validate()) {
		cout << "Order validated. Executing player "<<"[ "<<issuingPlayer->getPlayerId() <<" ]"<<" Advance Order"<< endl;
		//step 1 of execution: determine if its a move order or an attack order : Note: if its a null player, its automatically an attack
		if (target->getTerritoryOccupant() != NULL && target->getTerritoryOccupant()->getPlayerId() == issuingPlayer->getPlayerId()) {
			//we determined it is a move order
			cout << endl << "Player wants to advance armies in friendly Territory..." << endl;
			move();
		}
		else {
			//we determined it is an attack order. we verify if diplomacy exist between the two players
			cout << endl << "Player wants to advance armies in enemy Territory..." << endl;
			cout << endl << "Starting attack attempt... Verifying if diplomacy exists..." << endl;
			if (isDiplomacyDeclared()) { cout << endl << "Attempt at attacking Failed. There exist a diplomacy between the two players" << endl; }
			else {
				cout << endl << "No Diplomacy Exist... get ready for BATTLE !!" << endl;
				//resultingStats format: [resultingStats[0]:armies that attacked ||resultingStats[1] attackerEliminations ||resultingStats[2] defenderEliminations]
				vector<int> resultingStats = attack();
				//Now we analyze results and determine the outcome
				if (resultingStats.size() == 0) { cout << "Attack did not occur due to missing armies." << endl; }
				else {
					DisplayBattleResult(resultingStats);
					if (target->getNumArmies() - resultingStats[1] <= 0) {//resultingStats[1] = attackerEliminations
						//territory has been conquered
						conquer(resultingStats);
					}
					else {
						//territory was not conquered
						defeatDamageControl(resultingStats);
					}
				}
			}
		}
		setorderState(true); // Order Deploy is Executed
	}
	else {
		cout << "Cannot Execute Advance order: Order is invalid." << endl;
	}
}

//Constructor 
Advance::Advance() {
	setorderName("advance");
	setorderState(false);
	cout << "Advance Constructed: " << endl;
}

Advance::Advance(int armies, Territory* source_t, Territory* target_t, Player* player) {
	setorderName("advance");
	setorderState(false);
	cout << "Advance Constructed: " << endl;
	armiesToAdvance = armies;
	target = target_t;
	source = source_t;
	issuingPlayer = player;
}

//De-constructor 
Advance::~Advance() {
	cout << "Advance De-constructed: " << endl;
}

Advance::Advance(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}

//OverLoaded Assignment Operator
Advance& Advance::operator=(Advance& advance) {
	if (this == &advance) {
		return *this;
	}
	(*this).setorderState(advance.getorderState());
	(*this).setorderName(advance.getorderName());
	return *this;
}

bool Advance::isDiplomacyDeclared() {
	//we verify if the targeted player has the issuing player on its diplomacy list. if yes, we return true meaning the issuing player cannot attack
	if (target->getTerritoryOccupant() == NULL) { return false; }
	else {
		int targetedPlayerDiplomacyListSize = target->getTerritoryOccupant()->getDiplomacies().size();
		vector<int> targetedPlayerDiplomacyList = target->getTerritoryOccupant()->getDiplomacies();
		for (int i = 0; i < targetedPlayerDiplomacyListSize; i++) {

			if (targetedPlayerDiplomacyList[i] == issuingPlayer->getPlayerId()) {
				return true;
			}
		}
		return false;
	}
}

void Advance::move() {
	//step 1: verify if there is enough army to move
	if (source->getNumArmies() - 1 >= armiesToAdvance) {
		cout << endl << "Moving " << armiesToAdvance << " armies from " << source->getName() << " to " << target->getName() << endl;
		source->addNumArmies(-armiesToAdvance);//adding the negative the amount means removing armies
		target->addNumArmies(armiesToAdvance);
		cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
		cout << endl << *source << endl << endl;
		cout << endl << *target << endl << endl;

	}
	else {
		//design decision: we will move what ever is left and keep one on the territory
		if (source->getNumArmies() > 1) {
			int armiesToMove = source->getNumArmies() - 1;
			target->addNumArmies(armiesToMove);
			cout << endl << "Moving " << armiesToMove << " from " << source->getName() << " to " << target->getName() << endl;
			source->addNumArmies(-armiesToMove);//adding the negative the amount means removing armies
			target->addNumArmies(armiesToMove);
			cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
			cout << endl << *source << endl << endl;
			cout << endl << *target << endl << endl;
		}
		else {
			cout << endl << "attempt at moving armies failed. Not enough Armies" << endl;
		}
	}
}

vector<int> Advance::attack() {
	//attack mechanics explained: randomizing an integer from 1 to 10. if the number is between [1 and 6] attacker eliminates a soldier on the defense
	//once all attacking soldiers have attacked, we repeat the same with the defending armies, this time however, the defender eliminates attacking
	//soliders for numbers between [1 and 7]
	vector<int> resultingStats;
	int armiesToAttackWith = 0;
	if (source->getNumArmies() - 1 <= armiesToAdvance) {
		//design choice: if not enough armies, we attack with whats available as long as we keep one behind
		if (source->getNumArmies() > 1) {
			armiesToAttackWith = source->getNumArmies() - 1;
			source->addNumArmies(-armiesToAttackWith);//adding the negative the amount means removing armies
		}
		else {
			//not enough armies to attack
			return resultingStats;
		}
	}
	else {
		armiesToAttackWith = armiesToAdvance;
		source->addNumArmies(-armiesToAttackWith);//adding the negative the amount means removing armies
	}
	displayBattleComposition(armiesToAttackWith);
	resultingStats = runBattleMechanics(armiesToAttackWith);
	return resultingStats;

}

vector<int> Advance::runBattleMechanics(int armiesToAttackWith) {
	vector<int> resultingStats;
	resultingStats.push_back(armiesToAttackWith);
	int attackerEliminations = 0;
	cout << endl << "Attacker rolling dices... GO DICE ROLL!!! " << endl;
	for (int i = 0; i < armiesToAttackWith; i++) {
		int diceRoll = (int)(rand() % 10) + 1;

		if (diceRoll >= 1 && diceRoll <= 6) {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " Eliminates one defender" << endl;
			attackerEliminations++;
		}
		else {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " does not  Eliminate any defender" << endl;
		}
		diceRoll = 0;
	}
	resultingStats.push_back(attackerEliminations);
	int defenderEliminations = 0;
	int defendingArmies = target->getNumArmies();
	cout << endl << "Defender rolling dices... GO DICE ROLL!!! " << endl;
	for (int i = 0; i < defendingArmies; i++) {
		int diceRoll = rand() % 10 + 1;
		if (diceRoll >= 1 && diceRoll <= 7) {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " Eliminates one attacker" << endl;
			defenderEliminations++;
		}
		else {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " does not  Eliminate any attacker" << endl;
		}
		diceRoll = 0;
	}
	resultingStats.push_back(defenderEliminations);
	return resultingStats;
}

void Advance::displayBattleComposition(int armiesToAttackWith) {
	cout << endl << "===========BATTLE COMPOSITION DISPLAY===========" << endl;
	cout << endl << "[ATTACKER INFO] : Attacker Name: " << "[ " << issuingPlayer->getPlayerName() << " ]" << " Attacker ID: " << "[ " << issuingPlayer->getPlayerId() << " ]" << endl;
	if (target->getTerritoryOccupant() == NULL) {
		cout << endl << "[DEFENDER INFO] : NULL PLAYER" << endl;
	}
	else {
		cout << endl << "[DEFENDER INFO] : Defender Name: " << "[ " << target->getTerritoryOccupant()->getPlayerName() << " ]" << " Attacker ID: " << "[ " << target->getTerritoryOccupant()->getPlayerId() << " ]" << endl;
	}
	cout << endl << "Attacking Territory Name: " << "[ " << source->getName() << " ]" << " Attacking Territory ID: " << "[ " << source->getTerritoryID() << " ]" << endl;
	cout << endl << "Defender Territory Name: " << "[ " << target->getName() << " ]" << " Defender Territory ID " << "[ " << target->getTerritoryID() << " ]" << endl;
	cout << endl << "Attacker will be attacking with: " << armiesToAttackWith << " armies." << endl;
	cout << endl << "Attacker has: " << source->getNumArmies() << " Left on source territory" << endl;
	cout << endl << "Defender will be defending with: " << target->getNumArmies() << " armies. Stay tuned" << endl;
	cout << endl << "====================END BATTLE COMPOSITION DISPLAY ==========================" << endl;
}
void Advance::DisplayBattleResult(vector<int> resultingStats) {
	cout << endl << "===========BATTLE RESULTS===========" << endl;
	cout << endl << "Attacker eliminated " << ((resultingStats[1] > target->getNumArmies()) ? target->getNumArmies() : resultingStats[1]) << " defenders" << endl;//resultingStats[1] = attackerEliiminations || target->getNumArmies() = armies on defending territory
	cout << endl << "Defender now has " << ((target->getNumArmies() - resultingStats[1] > 0) ? target->getNumArmies() - resultingStats[1] : 0) << " armies" << endl;//resultingStats[1] = attackerEliiminations || target->getNumArmies() = armies on defending territory
	cout << endl << "Defender eliminated " << ((resultingStats[2] > resultingStats[0]) ? resultingStats[0] : resultingStats[2]) << " attackers" << endl;//resultingStats[2] = defenderEliminations || result[0] = attacking armies
	cout << endl << "Remaining attacking armies = " << ((resultingStats[0] - resultingStats[2] > 0) ? resultingStats[0] - resultingStats[2] : 0) << " armies" << endl;//resultingStats[2] = defenderEliminations || result[0] = attacking armies
	//the reason why we use conditional if statement is because an attacker or defender could have eliminated more armies than needed. for that case we change the display
}

void Advance::conquer(vector<int> resultingStats) {
	cout << endl << "Attacker WINS !!!" << endl;
	if (resultingStats[0] - resultingStats[2] <= 0) {//resultingStats[0] = armiesAttackedWith || resultingStats[2] = defenderEliminations 
		//no armies to move to new territory. new territory will have 0 army by game design choice
		target->setNumArmies(0);
	}
	else {
		int occupyingArmies = resultingStats[0] - resultingStats[2];
		target->setNumArmies(occupyingArmies);


	}
	//at this point, we first remove the territory from the list of territories of previous owner, then we set the new owner of the gained territory
	//and finally we add that new territory to the issuing player's territory list
	target->getTerritoryOccupant()->removeTerritoryFromList(target->getTerritoryID() - 1);//target->getTerritoryOccupant(): old territory occupant
	target->setTerritoryOccupant(issuingPlayer);//issuing player: new territory occupant
	issuingPlayer->assignTerritoryToPlayer(target);
	if (!issuingPlayer->getConquererFlag()) {
		//giving new card to player because he conquered a territory for the first time
		if (Player::common_deck != NULL) {
			if (Player::common_deck->getDeckSize() > 0) {
				Card* card = Player::common_deck->draw();
				cout << endl << "First territory conquered in the Turn... Player's gets a card " << endl;
				cout << endl << "Here it the new card Drawn: " << *card << endl;
				if (issuingPlayer->getPlayerHand() != NULL) {
					issuingPlayer->getPlayerHand()->addCardToHand(card);
					cout << endl << "Here is the player's new Hand: " << endl << *issuingPlayer->getPlayerHand() << endl;
				}
				else {
					cout << endl << "Player does not have any Hand setup. Consider setting a hand object for player before game begins" << endl;
					cout << endl << "Program will now terminate" << endl;
					exit(0);
				}
			}
			else {
				cout << endl << "The deck is empty. Card was not added to player's hand" << endl;
			}
		}
		else {
			cout << endl << "Player's common deck has not been initialized. cannot draw card" << endl;
		}
	}
	else {
		cout << endl << "Not the first territory conquered this turn... Player does not get a card" << endl;
	}
	cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
	cout << endl << *source << endl << endl;
	cout << endl << *target << endl << endl;
}

void Advance::defeatDamageControl(vector<int> resultingStats) {
	cout << endl << "Defender WINS !!!" << endl;
	int returningAttackers = resultingStats[0] - resultingStats[2]; //resultingStats[0] = armies that attacked || resultingStats[1] = attackerEliminations || resultingStats[2] = defenderEliminations
	//if there are attackers to add back to the source territory
	if (returningAttackers > 0) { source->addNumArmies(returningAttackers); }
	//remove eliminated defenders
	target->addNumArmies(-resultingStats[1]);//resultingStats[1] = attackerEliminations
	cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
	cout << endl << *source << endl << endl;
	cout << endl << *target << endl << endl;
}


// Bomb
bool Bomb::validate() {
	//step 1: validate if player has bomb card. if yes: play card and continue to step 2. if not, return false.
	cout << endl << "Executing Player " << "[ " << issuingPlayer->getPlayerId() << " ]" << " Bomb order" << endl;
	cout << endl << "Step1: Verify if Player has bomb card in hand..." << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(2)) {
		cout << endl << "Card not found. Cannot execute order... " << endl;
		return false;
	}
	issuingPlayer->getPlayerHand()->play(2, Player::common_deck);//we play card even if validate function returns false.
	cout << endl << "Step1 SUCCESS. Found bomb card... Proceeding to step2" << endl;
	cout << endl << "Step2: Verify that target territory belongs to enemy" << endl;
	if (target->getTerritoryOccupant() == NULL) {
		cout << endl << "Step2: SUCCESS. Territory belongs to enemy" << endl;
		return true;
	}
	if (target->getTerritoryOccupant()->getPlayerId() == issuingPlayer->getPlayerId()) { 
		cout << endl << "Step2 FAIL... Territory belongs to issuing player. SUICIDE MISSION ABORT!!!" << endl;
		return false; 
	}
	cout << endl << "Step2: SUCCESS. Territory belongs to enemy" << endl;
	return true;
}
void Bomb::execute(int playerIndex) {
	if (validate()) {
		cout <<endl<< "Validation complete. Commencing execution of player "<<issuingPlayer->getPlayerId()<<" Bomb order" << endl;
		cout <<endl<< "Mission Control to Heaver Bombers 963...Mission is a go..." << endl;
		cout <<endl<< "Heavy Bombers to Mission Control... We have visual on the target. Sending target's pre state report" << endl;
		displayBombResult();
		cout << endl << "Heavy Bombers to Mission Control... deploying Bombs... may god have mercy on their souls" << endl;
		cout << endl << "*******BLAST*******"<< endl;
		int currentNumArmies = target->getNumArmies();
		int resultingArmies = currentNumArmies / 2;
		target->setNumArmies(resultingArmies);
		cout << endl << "Heaver Bombers to Mission Control... Bombes successully landed on target... Sending in target's post state report"<< endl;
		displayBombResult();
		cout << endl << "Mission Control to heaver bombers... mission complete... time to come back home boys" << endl;
		setorderState(true); // Order Deploy is Executed
	}
	else {
		cout << endl << "Cannot execute Bomb order. Order is invalid" << endl;
	}
}

void Bomb::displayBombResult() {
	cout << endl << "=========================" << endl;
	cout << endl << "       TARGET REPORT       " << endl;
	cout << endl << "=========================" << endl;
	cout << endl << *target;	
}
//Constructor 
Bomb::Bomb() {
	setorderName("bomb");
	setorderState(false);
	cout << "Bomb Constructed: " << endl;
}

Bomb::Bomb(Player* player, Territory* target_t) {
	setorderName("bomb");
	setorderState(false);
	cout << "Bomb Constructed: " << endl;
	issuingPlayer = player;
	target = target_t;
}
//De-constructor 
Bomb::~Bomb() {
	cout << "Bomb De-constructed: " << endl;
}
Bomb::Bomb(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Bomb& Bomb::operator=(Bomb& bomb) {
	if (this == &bomb) {
		return *this;
	}
	(*this).setorderState(bomb.getorderState());
	(*this).setorderName(bomb.getorderName());
	return *this;
}


//Blockade
bool Blockade::validate() {
	//step 1: validate if player has blockade card. if yes: play card and continue to step 2. if not, return false.
	cout << endl << "Executing Player "<<"[ "<<issuingPlayer->getPlayerId()<<" ]"<<" Blockade order"<< endl;
	cout << endl << "STEP1:  Verify is Player has blockade card in hand..." << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(3)) {
		cout << endl << "STEP 1 FAIL. Card not found. Cannot execute order... " << endl;
		return false;
	}
	else {
		cout << endl << "STEP 1 SUCCESS. card found. Playing card...proceeding to next step " << endl;
		issuingPlayer->getPlayerHand()->play(3, Player::common_deck);//we play card even if validate function returns false.
		//step 2: validate to make sure target territory belongs to player
		cout << endl << "STEP2: Verify if terrtitory belongs to player..." << endl;
		for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
			if (targetTerritory->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
				cout << endl << "STEP2 SUCCESS. Territory belongs to player" << endl;
				return true;
			}
		}
		cout << endl << "STEP2 FAIL. Territory does not belong to player" << endl;
		return false;
	}

}
void Blockade::execute(int playerIndex) {
	if (validate()) {
		cout << endl << "Order validated. Commencing Execution of player "<<issuingPlayer->getPlayerId() <<" blockade order" << endl;
		//step 1: doubling territory armies
		int currentArmyAmount = targetTerritory->getNumArmies();
		targetTerritory->addNumArmies(currentArmyAmount);
		setorderState(true); // Order Deploy is Executed
		//step 2: setting the territory to vacant
		targetTerritory->setTerritoryOccupant(NULL);
		//step 3: removing territory from player's list
		int territoryIndex = targetTerritory->getTerritoryID() - 1;
		issuingPlayer->removeTerritoryFromList(territoryIndex);
		setorderState(true);
		displayBlockedTerritory();

	}
	else {
		cout << "Cannot Execute blockade order: Order is invalid."<<endl;
	}
}

void Blockade::displayBlockedTerritory(){
	cout << endl << "==========================" << endl;
	cout << endl << "   BLOCKED TERRITORY      " << endl;
	cout << endl << "==========================" << endl;
	cout << endl << *targetTerritory << endl;
}

//Constructor 
Blockade::Blockade() {
	setorderName("blockade");
	setorderState(false);
	cout << "Blockade Constructed: " << endl;
}
Blockade::Blockade(Player* player,Territory* territory) {
	issuingPlayer = player;
	targetTerritory = territory;
	setorderName("blockade");
	setorderState(false);
	cout << "Blockade Constructed: " << endl;
}
//De-constructor 
Blockade::~Blockade() {
	cout << "Blockade De-constructed: " << endl;
}
Blockade::Blockade(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Blockade& Blockade::operator=(Blockade& blockade) {
	if (this == &blockade) {
		return *this;
	}
	(*this).setorderState(blockade.getorderState());
	(*this).setorderName(blockade.getorderName());
	return *this;
}


// Airlift
bool Airlift::validate() {
	//step 1: validate if player has an airlift card. if yes: play card and continue to step 2. if not, return false.
	cout << endl << "Executing Airlift order...STEP1: Looking for Airlift card in hand" << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(1)) {
		cout << endl << "STEP1 FAIL.Card not found... Cannot execute order" << endl;
		return false;
	}
	else {
		cout << endl << "STEP1 SUCCESS. card found.Card played. Proceeding to step 2... " << endl;
		issuingPlayer->getPlayerHand()->play(1, Player::common_deck);//we play card even if validate function returns false.
		//step 2: validate to make sure that source territory belongs to issuingPlayer
		cout << endl << "STEP2: Validating if source territory belongs to player..." << endl;
		for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
			if (source->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
				cout << endl << "STEP2: SUCCESS. source territory belongs to player" << endl;
				return true;
			}

		}
		cout << endl << "STEP2: FAIL. source territory does not belongs to player" << endl;
		return false;
	}
}
void Airlift::execute(int playerIndex) {
	if (validate()) {
		cout << "Order validated. Starting execution for Player "<<issuingPlayer->getPlayerId()<<" Airlift Order" << endl;
		//step 1 of execution: determine if its a move order or an attack order : Note: if its a null player, its automatically an attack
		if (target->getTerritoryOccupant() !=NULL && target->getTerritoryOccupant()->getPlayerId() == issuingPlayer->getPlayerId()) {
			//we determined it is a move order
			cout << endl << "Player wants to drop armies in friendly Territory..." << endl;
			move();
		}
		else {
			//we determined it is an attack order. we verify if diplomacy exist between the two players
			cout << endl << "Player wants to drop armies in enemy Territory..." << endl;
			cout << endl << "Starting attack attempt... Verifying if diplomacy exists..." << endl;
			if(isDiplomacyDeclared()){ cout << endl << "Attempt at attacking Failed. There exist a diplomacy between the two players" << endl; }
			else {
				cout << endl << "No Diplomacy Exist... get ready for BATTLE !!" << endl;
				//resultingStats format: [resultingStats[0]:armies that attacked ||resultingStats[1] attackerEliminations ||resultingStats[2] defenderEliminations]
				vector<int> resultingStats = attack();
				//Now we analyze results and determine the outcome
				if (resultingStats.size() == 0) { cout << "Attack did not occur due to missing armies." << endl; }
				else {
					DisplayBattleResult(resultingStats);
					if (target->getNumArmies() - resultingStats[1] <= 0) {//resultingStats[1] = attackerEliminations
						//territory has been conquered
						conquer(resultingStats);
					}
					else {
						//territory was not conquered
						defeatDamageControl(resultingStats);
					}
				}
			}
		}
		setorderState(true); // Order Deploy is Executed
	}
	else {
		cout << "Cannot Execute airlift order: Order is invalid." << endl;
	}
}


bool Airlift::isDiplomacyDeclared() {
	//we verify if the targeted player has the issuing player on its diplomacy list. if yes, we return true meaning the issuing player cannot attack
	if (target->getTerritoryOccupant() == NULL) { return false; }
	else {
		int targetedPlayerDiplomacyListSize = target->getTerritoryOccupant()->getDiplomacies().size();
		vector<int> targetedPlayerDiplomacyList = target->getTerritoryOccupant()->getDiplomacies();
		for (int i = 0; i < targetedPlayerDiplomacyListSize; i++) {

			if (targetedPlayerDiplomacyList[i] == issuingPlayer->getPlayerId()) {
				return true;
			}
		}
		return false;
	}
}

void Airlift::move() {
	//step 1: verify if there is enough army to move
	if (source->getNumArmies() - 1 >= armiesToAdvance) {
		cout << endl << "Moving "<<armiesToAdvance <<"from "<<source->getName()<<" to "<<target->getName()<< endl;
		source->addNumArmies(-armiesToAdvance);//adding the negative the amount means removing armies
		target->addNumArmies(armiesToAdvance);
		cout<<endl<< "======NEW TERRITORY COMPOSITION=====" << endl;
		cout << endl << *source << endl << endl;
		cout << endl << *target << endl << endl;

	}
	else {
		//design decision: we will move what ever is left and keep one on the territory
		if (source->getNumArmies() > 1) {
			int armiesToMove = source->getNumArmies() - 1;
			target->addNumArmies(armiesToMove);
			cout << endl << "Moving " << armiesToMove << " armies from " << source->getName() << " to " << target->getName() << endl;
			source->addNumArmies(-armiesToMove);//adding the negative the amount means removing armies
			target->addNumArmies(armiesToMove);
			cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
			cout << endl << *source << endl << endl;
			cout << endl << *target << endl << endl;
		}
		else {
			cout << endl << "attempt at moving armies failed. Not enough Armies" << endl;
		}
	}
}

vector<int> Airlift::attack() {
	//attack mechanics explained: randomizing an integer from 1 to 10. if the number is between [1 and 6] attacker eliminates a soldier on the defense
	//once all attacking soldiers have attacked, we repeat the same with the defending armies, this time however, the defender eliminates attacking
	//soliders for numbers between [1 and 7]
	vector<int> resultingStats;
	int armiesToAttackWith = 0;
	if (source->getNumArmies() - 1 <= armiesToAdvance) {
		//design choice: if not enough armies, we attack with whats available as long as we keep one behind
		if (source->getNumArmies() > 1) {
			armiesToAttackWith = source->getNumArmies() - 1;
			source->addNumArmies(-armiesToAttackWith);//adding the negative the amount means removing armies
		}
		else {
			//not enough armies to attack
			return resultingStats;
		}
	}
	else { 
		armiesToAttackWith = armiesToAdvance; 
		source->addNumArmies(-armiesToAttackWith);//adding the negative the amount means removing armies
	}
	displayBattleComposition(armiesToAttackWith);
	resultingStats = runBattleMechanics(armiesToAttackWith);
	return resultingStats;

}

vector<int> Airlift::runBattleMechanics(int armiesToAttackWith) {
	vector<int> resultingStats;
	resultingStats.push_back(armiesToAttackWith);
	int attackerEliminations = 0;
	cout << endl <<"Attacker rolling dices... GO DICE ROLL!!! " << endl;
	for (int i = 0; i < armiesToAttackWith; i++) {
		int diceRoll = (int) (rand() % 10)+ 1;
		
		if (diceRoll>=1 && diceRoll<=6) {
			cout << endl << "Dice roll result "<< diceRoll<<" Army#"<<i+1<<" Eliminates one defender" << endl;
			attackerEliminations++;
		}
		else {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " does not  Eliminate any defender" << endl;
		}
		diceRoll = 0;
	}
	resultingStats.push_back(attackerEliminations);
	int defenderEliminations = 0;
	int defendingArmies = target->getNumArmies();
	cout << endl << "Defender rolling dices... GO DICE ROLL!!! " << endl;
	for (int i = 0; i < defendingArmies; i++) {
		int diceRoll = rand() % 10 + 1;
		if (diceRoll>=1 &&  diceRoll<= 7) {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " Eliminates one attacker" << endl;
			defenderEliminations++;
		}
		else {
			cout << endl << "Dice roll result " << diceRoll << " Army#" << i + 1 << " does not  Eliminate any attacker" << endl;
		}
		diceRoll = 0;
	}
	resultingStats.push_back(defenderEliminations);
	return resultingStats;
}

void Airlift::displayBattleComposition(int armiesToAttackWith) {
	cout << endl << "===========BATTLE COMPOSITION DISPLAY===========" << endl;
	cout << endl << "[ATTACKER INFO] : Attacker Name: " << "[ " << issuingPlayer->getPlayerName() << " ]" << " Attacker ID: " << "[ " << issuingPlayer->getPlayerId() << " ]" << endl;
	if (target->getTerritoryOccupant() == NULL) {
		cout << endl << "[DEFENDER INFO] : NULL PLAYER"<< endl;
	}
	else {
		cout << endl << "[DEFENDER INFO] : Defender Name: " << "[ " << target->getTerritoryOccupant()->getPlayerName() << " ]" << " Attacker ID: " << "[ " << target->getTerritoryOccupant()->getPlayerId() << " ]" << endl;
	}
	cout << endl << "Attacking Territory Name: " <<"[ "<< source->getName()<<" ]" << " Attacking Territory ID: "<< "[ "<<source->getTerritoryID()<<" ]"<<endl;
	cout << endl << "Defender Territory Name: " << "[ " << target->getName() << " ]" << " Defender Territory ID " << "[ " << target->getTerritoryID() << " ]" << endl;
	cout << endl << "Attacker will be attacking with: " << armiesToAttackWith << " armies." << endl;
	cout << endl << "Attacker has: " << source->getNumArmies() << " Left on source territory" << endl;
	cout << endl << "Defender will be defending with: " << target->getNumArmies() << " armies. Stay tuned" << endl;
	cout << endl << "====================END BATTLE COMPOSITION DISPLAY ==========================" << endl;
}
void Airlift::DisplayBattleResult(vector<int> resultingStats) {
	cout << endl << "===========BATTLE RESULTS===========" << endl;
	cout << endl << "Attacker eliminated " << ((resultingStats[1]>target->getNumArmies())? target->getNumArmies(): resultingStats[1]) << " defenders" << endl;//resultingStats[1] = attackerEliiminations || target->getNumArmies() = armies on defending territory
	cout << endl << "Defender now has " << ( (target->getNumArmies() - resultingStats[1] >0) ? target->getNumArmies() - resultingStats[1]  : 0) << " armies" << endl;//resultingStats[1] = attackerEliiminations || target->getNumArmies() = armies on defending territory
	cout << endl << "Defender eliminated " << ((resultingStats[2]>resultingStats[0]) ?resultingStats[0]:resultingStats[2]) << " attackers" << endl;//resultingStats[2] = defenderEliminations || result[0] = attacking armies
	cout << endl << "Remaining attacking armies = " <<( (resultingStats[0] - resultingStats[2] > 0) ? resultingStats[0] - resultingStats[2] : 0)<< " armies" << endl;//resultingStats[2] = defenderEliminations || result[0] = attacking armies
	//the reason why we use conditional if statement is because an attacker or defender could have eliminated more armies than needed. for that case we change the display
}

void Airlift::conquer(vector<int> resultingStats) {
	cout <<endl<< "Attacker WINS !!!" << endl;
	if (resultingStats[0] - resultingStats[2] <= 0) {//resultingStats[0] = armiesAttackedWith || resultingStats[2] = defenderEliminations 
		//no armies to move to new territory. new territory will have 0 army by game design choice
		target->setNumArmies(0);
	}
	else {
		int occupyingArmies = resultingStats[0] - resultingStats[2];
		target->setNumArmies(occupyingArmies);

	}
	target->getTerritoryOccupant()->removeTerritoryFromList(target->getTerritoryID() - 1);//target->getTerritoryOccupant(): old territory occupant
	target->setTerritoryOccupant(issuingPlayer);//issuing player: new territory occupant
	issuingPlayer->assignTerritoryToPlayer(target);
	if (!issuingPlayer->getConquererFlag()) {
		//giving new card to player because he conquered a territory for the first time
		if (Player::common_deck->getDeckSize() > 0) {
			Card* card = Player::common_deck->draw();
			cout << endl << "First territory conquered in the Turn... Player's gets a card " << endl;
			cout << endl << "Here it the new card Drawn: "<<*card << endl;
			issuingPlayer->getPlayerHand()->addCardToHand(card);
			cout << endl << "Here is the player's new Hand: " << endl << *issuingPlayer->getPlayerHand() << endl;
		}
		else {
			cout << endl << "The deck is empty. Card was not added to player's hand" << endl;
		}
		issuingPlayer->setConquererFlag(true);
	}
	else {
		cout << endl << "The player will not gain a card... It is not the first territory conquered this turn" << endl;
	}
	cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
	cout << endl << *source << endl << endl;
	cout << endl << *target << endl << endl;

}

void Airlift::defeatDamageControl(vector<int> resultingStats) {
	cout << endl << "Defender WINS !!!" << endl;
	int returningAttackers = resultingStats[0] - resultingStats[2]; //resultingStats[0] = armies that attacked || resultingStats[1] = attackerEliminations || resultingStats[2] = defenderEliminations
	//if there are attackers to add back to the source territory
	if (returningAttackers > 0) { source->addNumArmies(returningAttackers); }
	//remove eliminated defenders
	target->addNumArmies(-resultingStats[1]);//resultingStats[1] = attackerEliminations
	cout << endl << "======NEW TERRITORY COMPOSITION=====" << endl;
	cout << endl << *source << endl << endl;
	cout << endl << *target << endl << endl;
}

//Constructor 
Airlift::Airlift() {
	setorderName("airlift");
	setorderState(false);
	cout << "Airlift Constructed: " << endl;
}

Airlift::Airlift(int armies, Territory* source_t, Territory* target_t, Player* player) {
	setorderName("airlift");
	setorderState(false);
	cout << "Airlift Constructed: " << endl;
	armiesToAdvance = armies;
	target = target_t;
	source = source_t;
	issuingPlayer = player;
}
//De-constructor 
Airlift::~Airlift() {
	cout << "Airlift De-constructed: " << endl;
}

Airlift::Airlift(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}

//OverLoaded Assignment Operator
Airlift& Airlift::operator=(Airlift& airlift) {
	if (this == &airlift) {
		return *this;
	}
	(*this).setorderState(airlift.getorderState());
	(*this).setorderName(airlift.getorderName());
	return *this;
}

// Negotiate
bool Negotiate::validate() {
	//step 1: validate if player has a negotiate card. if yes: play card and continue to step 2. if not, return false.
	cout << endl << "Executing Negotiate order...STEP1: Looking for Negotiate card in hand" << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(4)) {
		cout << endl << "STEP1 FAIL. Player does not have diplomacy card. Order is invalid" << endl;
		return false;
	}
	else {
		cout << endl << "STEP1 SUCCESS card found. Playing card...Proceeding to next step " << endl;
		issuingPlayer->getPlayerHand()->play(4, Player::common_deck);//we play card even if validate function returns false.
		cout << endl << "STEP2: Verifying that both players are not the same... " << endl;
		//step 2: validate to make sure target player is not same as issuingPlayer
		if (issuingPlayer->getPlayerId() != targetPlayer->getPlayerId()) {
			cout << endl << "STEP2 SUCCESS: Both players are not the same " << endl;
			return true;
		}
		else { 
			cout << endl << "STEP2 FAIL Negotiate order invalid. both players are the same" << endl;
			return false; 
		}
	}
}

void Negotiate::execute(int playerIndex) {
	if (validate()) {
		cout << "Order validated. Starting execution for Player[" << playerIndex << "] Negotiate Order: " << endl;
		issuingPlayer->declareDiplomacy(targetPlayer);//by declaring diplomacy the target player can no longer attack the issuing player in this turn
		setorderState(true);
		displayDiplomacies();
	}
	else {
		cout << endl << "Cannot execute Negotiate order. order is invalid" << endl;
	}

}
//Constructor 
Negotiate::Negotiate() {
	setorderName("negotiate");
	setorderState(false);
	cout << "Negotiate Constructed: " << endl;
}

Negotiate::Negotiate(Player* source, Player* target) {
	setorderName("negotiate");
	setorderState(false);
	cout << "Negotiate Constructed: " << endl;
	issuingPlayer = source;
	targetPlayer = target;
}

void Negotiate::displayDiplomacies() {
	cout << endl << "PLAYER DIPLOMACIES: " << endl;
	cout << endl << "Player " << "[ " << issuingPlayer->getPlayerId() << " ]" << " has declared a negotiate order with "
		         << "Player " << "[ " << targetPlayer->getPlayerId() << "  ]" << endl;
}

//De-constructor 
Negotiate::~Negotiate() {
	cout << "Negotiate De-constructed: " << endl;
}
Negotiate::Negotiate(Order& order) {
	(*this).setorderState(order.getorderState());
	(*this).setorderName(order.getorderName());
}
//OverLoaded Assignment Operator
Negotiate& Negotiate::operator=(Negotiate& negotiate) {
	if (this == &negotiate) {
		return *this;
	}
	(*this).setorderState(negotiate.getorderState());
	(*this).setorderName(negotiate.getorderName());
	return *this;
}

//Commit
bool Commit::validate() {
	return true;
}

void Commit::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Commit Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
}

//Constructor 
Commit::Commit() {
	setorderName("Commit");
	setorderState(false);
}

Commit::~Commit() {
}

ostream& operator << (ostream& output, Order& order) {
	if (order.getorderState() == false) {
		output << "The order name is: " << order.getorderName() << " and the order has not been exectuted yet. " << endl;
	}
	if (order.getorderState() == true) {
		output << "The order name is: " << order.getorderName() << " and the order has been exectuted." << endl;
	}
	return output;
}

// OrderList
void OrderList::add(Order* order) {
	allOrders.push_back(order);
	numSize++;
}
void OrderList::print() {
	for (int i = 0; i < numSize; i++) {
		cout << allOrders[i]->getorderName() << endl;
	}
}
void OrderList::move(int fromPos, int toPos) {
	if (fromPos > toPos) {
		allOrders.insert(allOrders.begin() + (toPos - 1), allOrders[fromPos - 1]); // inserts the element from old position to new position
		allOrders.erase(allOrders.begin() + fromPos); // erase the element from original position.
	}
	else if (toPos > fromPos) {
		Order* temp = allOrders[fromPos - 1];
		allOrders.insert(allOrders.begin() + (toPos), temp); // inserts the element from old position to new position
		allOrders.erase(allOrders.begin() + fromPos - 1); // erase the element from original position.
	}
	else {
		return;
	}
}

void OrderList::sort() {
	if (allOrders.size() < 2) { return; }
	else {
		int newOrderPos = allOrders.size() - 1;
		//the following if statement makes sure to not move an order if it is not one of the priority 3
		if (allOrders[newOrderPos]->getorderName() != "deploy" && allOrders[newOrderPos]->getorderName() != "airlift" && allOrders[newOrderPos]->getorderName() != "blockade") {
			return;
		}
		int positionToInsert = -1;
		for (int i = allOrders.size() -2 ; i>=0; i < i--) {
			if(allOrders[newOrderPos]->getorderName() == "deploy" ){
				if (allOrders[i]->getorderName() == "deploy") {
					positionToInsert = i + 2;//since the move position takes positions from 1 to vector size
					break;
				}
				else { continue; }
			}
			else if (allOrders[newOrderPos]->getorderName() == "airlift") {
				if (allOrders[i]->getorderName() == "deploy" || allOrders[i]->getorderName() == "airlift") {
					positionToInsert = i + 2;//since the move position takes positions from 1 to vector size
					break;
				}
				else { continue; }
			}
			else if (allOrders[newOrderPos]->getorderName() == "blockade") {
				if (allOrders[i]->getorderName() == "deploy" ||  allOrders[i]->getorderName() == "airlift" || allOrders[i]->getorderName() == "blockade") {
					positionToInsert = i + 2;//since the move position takes positions from 1 to vector size
					break;
				}
				else { continue; }
			}
		}
		if (positionToInsert == -1) {
			move(newOrderPos + 1, 1);
		}
		else {
			move(newOrderPos + 1, positionToInsert);
		}
	}
}
void OrderList::remove(int numRem) {
	delete(allOrders[numRem - 1]);
	allOrders.erase(allOrders.begin() + (numRem - 1));
	numSize--;
}
// Constructor
OrderList::OrderList() {
	// max number of commands allowed right now...
	numSize = 0;
}
// Copy Constructor- deep copy
OrderList::OrderList(const OrderList& orderlist) {
	cout << "Copy Constructor (deep copy): " << endl;
	numSize = orderlist.numSize;
	for (int i = 0; i < numSize; i++) {
		if (orderlist.allOrders[i]->getorderName() == "deploy") {
			allOrders.push_back(new Deploy(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "advance") {
			allOrders.push_back(new Advance(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "bomb") {
			allOrders.push_back(new Bomb(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "negotiate") {
			allOrders.push_back(new Negotiate(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "blockade") {
			allOrders.push_back(new Blockade(*orderlist.allOrders[i]));
		}
		if (orderlist.allOrders[i]->getorderName() == "airlift") {
			allOrders.push_back(new Airlift(*orderlist.allOrders[i]));
		}
	}
}
////OverLoaded Assignment Operator
OrderList& OrderList::operator=(const OrderList& orderlist) {
	cout << "Overloaded Assignment Operator (deep copy): " << endl;
	if (this == &orderlist) {
		return *this;
	}
	numSize = orderlist.numSize;
	for (int i = 0; i < numSize; i++) {
		if (orderlist.allOrders[i]->getorderName() == "deploy") {
			allOrders.push_back(new Deploy);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "advance") {
			allOrders.push_back(new Advance);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "bomb") {
			allOrders.push_back(new Bomb);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "negotiate") {
			allOrders.push_back(new Negotiate);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "blockade") {
			allOrders.push_back(new Blockade);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}
		if (orderlist.allOrders[i]->getorderName() == "airlift") {
			allOrders.push_back(new Airlift);
			allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
		}

	}
	return *this;
}

// Destructor
OrderList::~OrderList() {
	cout << "Destructor Called for OrderList." << endl;
	for (unsigned int i = 0; i < allOrders.size(); i++) {
		delete(allOrders[i]);
	}
}

string OrderList::peekLastOrder()
{
	return allOrders[allOrders.size() - 1]->getorderName();
}

ostream& operator << (ostream& output, OrderList& orderlist) {
	output << "Order-list has following orders: " << endl << "| ";
	for (unsigned int i = 0; i < orderlist.allOrders.size(); i++) {
		output << orderlist.allOrders[i]->getorderName() << " | ";
	}
	output << endl;
	return output;
}
