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
	cout << "Order Constructed: " << endl;
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
	for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
		if (target->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
			cout << endl << "Deploy order valid, ready to start execution phase..." << endl;
			return true;
		}
	}
	return false;
}
void Deploy::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Deploy order..." << endl;
		issuingPlayer->addToArmiesToBePlaced(armiesToDeploy);
		setorderState(true); // Order Deploy is Executed
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
	cout << "Deploy Constructed: " << endl;
}

Deploy::Deploy(int armies, Territory* target_t, Player* player) {
	setorderName("deploy");
	setorderState(false);
	cout << "Deploy Constructed: " << endl;
	armiesToDeploy = armies;
	target = target_t;
	issuingPlayer = player;
}

Deploy::~Deploy() {
	cout << "Deploy De-constructed: " << endl;
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
	return true;
}
void Advance::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Advance Order: " << endl;
		setorderState(true); // Order Deploy is Executed
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


// Bomb
bool Bomb::validate() {
	return true;
}
void Bomb::execute(int playerIndex) {
	if (validate()) {
		cout << "Executing Player[" << playerIndex << "] Bomb Order: " << endl;
		setorderState(true); // Order Deploy is Executed
	}
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
	if (!issuingPlayer->getPlayerHand()->isCardInHand(3)) {
		return false;
	}
	else {
		cout << endl << "card found. Playing card... " << endl;
		issuingPlayer->getPlayerHand()->play(3, Player::common_deck);//we play card even if validate function returns false.
		cout << endl << "New hand: " << endl;
		cout << endl << *issuingPlayer->getPlayerHand() << endl;
		//step 2: validate to make sure target territory belongs to player
		for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
			if (targetTerritory->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
				return true;
			}
		}
		return false;
	}

}
void Blockade::execute(int playerIndex) {
	if (validate()) {
		cout << endl << "Executing blockade order..." << endl;
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

	}
	else {
		cout << "Cannot Execute order: Order is invalid."<<endl;
	}
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
	cout << endl << "Executing Airlift order... Looking for Airlift card in hand" << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(1)) {
		return false;
	}
	else {
		cout << endl << "card found. Playing card... " << endl;
		issuingPlayer->getPlayerHand()->play(1, Player::common_deck);//we play card even if validate function returns false.
		//step 2: validate to make sure that source territory belongs to issuingPlayer
		cout << endl << "Validating if source territory belongs to player..." << endl;
		for (int i = 0; i < issuingPlayer->getPlayerTerritories().size(); i++) {
			if (source->getTerritoryID() == issuingPlayer->getPlayerTerritories()[i]->getTerritoryID()) {
				return true;
			}

		}
		return false;
	}
}
void Airlift::execute(int playerIndex) {
	if (validate()) {
		cout << "Order validated. Starting execution for Player[" << playerIndex << "] Airlift Order: " << endl;
		//step 1 of execution: determine if its a move order or an attack order
		if (target->getTerritoryOccupant()->getPlayerId() == issuingPlayer->getPlayerId()) {
			//we determined it is a move order
			cout << endl << "Player wants to drop armies in friendly Territory..." << endl;
			move();
		}
		else {
			//we determined it is an attack order. we verify if diplomacy exist between the two players
			cout << endl << "Player wants to drop armies in enemy Territory..." << endl;
			cout << endl << "Starting attack attempt... Verifying if diplomacy exists..." << endl;
			if (isDiplomacyDeclared()) { cout << endl << "Attempt at attacking Failed. Targeted player has declared diplomacy" << endl; }
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
		cout << "Cannot Execute order: Order is invalid." << endl;
	}
}


bool Airlift::isDiplomacyDeclared() {
	//we verify if the targeted player has the issuing player on its diplomacy list. if yes, we return true meaning the issuing player cannot attack
	int targetedPlayerDiplomacyListSize = target->getTerritoryOccupant()->getDiplomacies().size();
	vector<int> targetedPlayerDiplomacyList = target->getTerritoryOccupant()->getDiplomacies();
	for (int i = 0; i < targetedPlayerDiplomacyListSize; i++) {
		if (targetedPlayerDiplomacyList[i] == issuingPlayer->getPlayerId()) {
			return true;
		}
	}
	return false;
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
			cout << endl << "Moving " << armiesToMove << "from " << source->getName() << " to " << target->getName() << endl;
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
	cout << endl << "Remaining attacking armies = " <<( (resultingStats[0] - resultingStats[2] > 0) ? target->getNumArmies() : 0)<< " armies" << endl;//resultingStats[2] = defenderEliminations || result[0] = attacking armies
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
	target->setTerritoryOccupant(issuingPlayer);
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
	cout << endl << "Executing Negotiate order... Looking for Negotiate card in hand" << endl;
	if (!issuingPlayer->getPlayerHand()->isCardInHand(4)) {
		cout << endl << "Player does not have diplomacy card. Order is invalid" << endl;
		return false;
	}
	else {
		cout << endl << "card found. Playing card... " << endl;
		issuingPlayer->getPlayerHand()->play(4, Player::common_deck);//we play card even if validate function returns false.
		//step 2: validate to make sure target player is not same as issuingPlayer
		if (issuingPlayer->getPlayerId() != targetPlayer->getPlayerId()) {
			return true;
		}
		else { 
			cout << endl << "Negotiate order invalid. both players are the same" << endl;
			return false; 
		}
	}
}

void Negotiate::execute(int playerIndex) {
	if (validate()) {
		cout << "Order validated. Starting execution for Player[" << playerIndex << "] Negotiate Order: " << endl;
		issuingPlayer->declareDiplomacy(targetPlayer->getPlayerId());
		setorderState(true); // Order Deploy is Executed
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
			//allOrders[i]->setorderState(orderlist.allOrders[i]->getorderState());
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
//OrderList& OrderList::operator=(const OrderList& orderlist) {
//	cout << "OverLoaded Assignment Called: " << endl;
//	if (this == &orderlist) {
//		return *this;
//	}
//	this->numSize = orderlist.numSize;
//	for (int i = 0; i < numSize; i++) {
//		Order* copy(orderlist.allOrders[i]);
//		allOrders[i] = copy;
//	}
//	return *this;
//}

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

ostream& operator << (ostream& output, OrderList& orderlist) {
	output << "Order-list has following orders: " << endl << "| ";
	for (unsigned int i = 0; i < orderlist.allOrders.size(); i++) {
		output << orderlist.allOrders[i]->getorderName() << " | ";
	}
	output << endl;
	return output;
}
