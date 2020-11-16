
#include <iostream>
#include"Cards.h"
#include"Map.h"
#include "MapLoader.h"
#include"Player.h"
#include"GameEngine.h"

void part_4::start() {
	//creating game engine, creating map, loading canada map
	MapLoader* loader = new MapLoader();
	Map* map;
	map = new Map(loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);
	//creating deck and initializing static player variable common_deck
	Deck* deck = new Deck();
	Player::common_deck = deck;
	//filling deck with a card of each type
	Card* card1 = new Card(1);
	Card* card2 = new Card(2);
	Card* card3 = new Card(3);
	Card* card4 = new Card(4);
	Player::common_deck->addCardToDeck(card1);
	Player::common_deck->addCardToDeck(card2);
	Player::common_deck->addCardToDeck(card3);
	Player::common_deck->addCardToDeck(card4);
	//creating players, adding players to game engine
	Player* player1 = new Player(1, "Vishal", 0);
	Player* player2 = new Player(2, "Neil", 0);
	Player* player3 = new Player(3, "Paurush", 0);
	Player* player4 = new Player(4, "Martin", 0);
	//creading player hands
	Hand* hand_p1 = new Hand();
	Hand* hand_p2 = new Hand();
	Hand* hand_p3 = new Hand();
	Hand* hand_p4 = new Hand();
	//setting player's hand
	player1->setPlayerHand(hand_p1);
	player2->setPlayerHand(hand_p2);
	player3->setPlayerHand(hand_p3);
	player4->setPlayerHand(hand_p4);
	engine->addPlayer(player1);
	engine->addPlayer(player2);
	engine->addPlayer(player3);
	engine->addPlayer(player4);
	//assiging players to territories
	engine->getGameMap()->assignOccupantToTerritory(1, player1);
	engine->getGameMap()->assignOccupantToTerritory(2, player2);
	engine->getGameMap()->assignOccupantToTerritory(3, player3);
	engine->getGameMap()->assignOccupantToTerritory(8, player4);
	//assigning territories to players
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(1));
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(2));
	player3->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(3));
	player4->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(8));
	//setting initial army pool.
	player1->setArmyToBePlaced(10);
	player2->setArmyToBePlaced(10);
	player3->setArmyToBePlaced(5);//set to 5 to demonstrate failed deploy due to not enough armies
	player4->setArmyToBePlaced(10);
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 1      " << endl;
	cout << endl << "===============================" << endl;
	//DEMO STEP1: create and issue deploy orders. player 1 and 2 orders will succeed. player 3 and 4 will fail:
	//DEPLOY DOES NOT REQUIRE A CARD
	//player 1 successful deploy
	Order* order1 = new Deploy(10, engine->getGameMap()->getTerritory(1), player1);
	player1->issueOrder(order1);
	//player 2 successful deploy
	Order* order2 = new Deploy(10, engine->getGameMap()->getTerritory(2), player2);
	player2->issueOrder(order2);
	//player 3 fail[not enough army in pool] deploy order attempt
	Order* order3 = new Deploy(10, engine->getGameMap()->getTerritory(3), player3);//attempt at deploying 10 when only 5 is available
	player3->issueOrder(order3);
	//player 4 fail[territory does not belong to player] deploy order attempt
	Order* order4 = new Deploy(10, engine->getGameMap()->getTerritory(3), player4);//territory 3 belongs to player 3
	player4->issueOrder(order4);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP 2: deploying all armies to begin game
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 2      " << endl;
	cout << endl << "===============================" << endl;
	player3->setArmyToBePlaced(10);
	Order* order5 = new Deploy(10, engine->getGameMap()->getTerritory(3), player3);
	Order* order6 = new Deploy(10, engine->getGameMap()->getTerritory(8), player4);
	player3->issueOrder(order5);
	player4->issueOrder(order6);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "TERRITORIES IN DEMO" << endl;
	cout << endl << "=============================" << endl;
	cout << *engine->getGameMap()->getTerritory(1) << endl;
	cout << *engine->getGameMap()->getTerritory(2) << endl;
	cout << *engine->getGameMap()->getTerritory(3) << endl;
	cout << *engine->getGameMap()->getTerritory(8) << endl;
	cout << endl << "=============================" << endl;
	//DEMO STEP3: create and issue advance orders. player 1 and 2 orders will succeed. player 3 and 4 will fail
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 3      " << endl;
	cout << endl << "===============================" << endl;
	//adding new territory to player 1 and setting armies in army pool
	engine->getGameMap()->assignOccupantToTerritory(4, player1);
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(4));
	engine->getGameMap()->assignOccupantToTerritory(7, player1);
	player1->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(7));
	player1->setArmyToBePlaced(20);
	//creating deploy order, player 1 issues order, player 1 order executed for demo purposes
	Order* order7 = new Deploy(10, engine->getGameMap()->getTerritory(4), player1);
	Order* order8 = new Deploy(10, engine->getGameMap()->getTerritory(7), player1);
	player1->issueOrder(order7);
	player1->issueOrder(order8);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP4: create and issue advance orders. order 1 and 2 will pass. orders 3,4,5,and 6 will fail
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 4      " << endl;
	cout << endl << "===============================" << endl;
	//creating advance order1: Player 1 will move 7 armies from 4 to 7 and will succeed. 
	Order* order9 = new Advance(7, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(7), player1);
	player1->issueOrder(order9);
	//creating advance order2: Player 3 will advance armies from territory 3 to territory 4 creating an attack. he will attack with 9 armies
	//order will execute successfully. outcome to be determined.
	Order* order10 = new Advance(9, engine->getGameMap()->getTerritory(3), engine->getGameMap()->getTerritory(4), player3);
	player3->issueOrder(order10);
	//creating advance order3: Player 1 will try to advance armies from territory 4(formely his) to territory 7. will fail because source territory 
	//does not belong to issuing player
	Order* order11 = new Advance(5, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(7), player1);
	player1->issueOrder(order11);
	//create advance order4: Player 3 will now try to attack territory 8 but will fail because it is not adjacent
	Order* order12 = new Advance(9, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(8), player3);
	player3->issueOrder(order12);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP5: create and issue airlift orders. order 1 and 2 will fail, 3,4 will succeed.
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 5      " << endl;
	cout << endl << "===============================" << endl;
	//creating airlift order 1: player 3 will reattempt to attack territory 8 with airlift. attack will fail because player 3 might not have airlift card
	Order* order13 = new Airlift(4, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(8), player3);
	player3->issueOrder(order13);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating airlift order 2: player 1 will attempt at doing airlift from territory 8- which does not belong to him. attack will fail
	//adding airlift card to hand
	Card* card5 = new Card(1);
	hand_p1->addCardToHand(card5);
	cout << endl << "Player has now added an airlift card in hand" << endl;
	Order* order14 = new Airlift(10, engine->getGameMap()->getTerritory(8), engine->getGameMap()->getTerritory(4), player1);
	player1->issueOrder(order14);
	//creating airlift order 3: player 1 will now to take back territory 4 by doing an airlift from territory 7 to territory 4.attack will succeed
	//adding airlift card to hand
	Card* card6 = new Card(1);
	hand_p1->addCardToHand(card6);
	cout << endl << "Player has now added an airlift card in hand" << endl;
	Order* order15 = new Airlift(10, engine->getGameMap()->getTerritory(7), engine->getGameMap()->getTerritory(4), player1);
	player1->issueOrder(order15);
	//creating airlift order 4: player 1 will airlift from territory 1 to territory 3. Attack will succeed but player won't gain a card
	Order* order16 = new Airlift(7, engine->getGameMap()->getTerritory(1), engine->getGameMap()->getTerritory(3), player1);
	player1->issueOrder(order16);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "===================================" << endl;
	cout << endl << "  DISPLAYING STARTS AFTER PART 5   " << endl;
	cout << endl << "===================================" << endl;
	cout << endl << "TERRITORIES IN DEMO" << endl;
	cout << endl << "=============================" << endl;
	cout << *engine->getGameMap()->getTerritory(1) << endl;
	cout << *engine->getGameMap()->getTerritory(2) << endl;
	cout << *engine->getGameMap()->getTerritory(3) << endl;
	cout << *engine->getGameMap()->getTerritory(4) << endl;
	cout << *engine->getGameMap()->getTerritory(7) << endl;
	cout << *engine->getGameMap()->getTerritory(8) << endl;
	//DEMO STEP6: create and issue blockade orders. order 1 and 2 will fail, the third will succeed
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 6      " << endl;
	cout << endl << "===============================" << endl;
	//creating blockade order 1: player 2 attempts to create blockade but does not have blockade card. order fails
	Order* order17 = new Blockade(player4, engine->getGameMap()->getTerritory(8));
	player4->issueOrder(order17);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//adding blockade card to hand
	Card* card7 = new Card(3);
	hand_p4->addCardToHand(card7);
	cout << endl << "Player has now added an blockade card in hand" << endl;
	//creating blockade order 2: player 2 is able to use blockade card but territory does not belong to him
	Order* order18 = new Blockade(player4, engine->getGameMap()->getTerritory(1));
	player4->issueOrder(order18);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating blockade order 3: player 2 is able to use blockade card and blockade is successful
	Card* card8 = new Card(3);
	hand_p4->addCardToHand(card8);
	cout << endl << "Player has now added an blockade card in hand" << endl;
	cout << endl << "==============================" << endl;
	cout << endl << "   PLAYER 4 INFO BEFORE BLK   " << endl;
	cout << endl << "==============================" << endl;
	cout << *player4;
	Order* order19 = new Blockade(player4, engine->getGameMap()->getTerritory(8));
	player4->issueOrder(order19);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "==============================" << endl;
	cout << endl << "    PLAYER 4 INFO AFTER BLK   " << endl;
	cout << endl << "==============================" << endl;
	cout << *player4;
	cout << endl << "==============================" << endl;
	//DEMO STEP7: create and issue Negotiate orders. player 1 and 2 orders will succeed. player 3 and 4 will fail
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 7      " << endl;
	cout << endl << "===============================" << endl;
	//DEMO STEP7: create and issue Negotiate orders.order 1 and 2 will fail, order 3 will succeed. then attempt at attacking by both players in the negotiation fails
	//creating negotiate order 1: player two issues negotiate order but it  fails because no diplomacy card
	Order* order20 = new Negotiate(player2, player1);
	player2->issueOrder(order20);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating negotiate order 2: a card is added in the player2's hand, but player 2 issues a negotiation with himself
	Card* card9 = new Card(4);
	hand_p2->addCardToHand(card9);
	cout << endl << "Player has now added a Diplomacy card in hand" << endl;
	Order* order21 = new Negotiate(player2, player2);
	player2->issueOrder(order21);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating negotiate order 3: player 1 now issues negotiate order and it succeeds
	Card* card10 = new Card(4);
	hand_p1->addCardToHand(card10);
	cout << endl << "Player has now added a Diplomacy  card in hand" << endl;
	Order* order22 = new Negotiate(player1, player2);
	player1->issueOrder(order22);
	//player 1 issues attack on territory of player 2 and fails due to diplomacy
	Order* order23 = new Advance(5, engine->getGameMap()->getTerritory(3), engine->getGameMap()->getTerritory(2),player1);
	player1->issueOrder(order23);
	//player 2 issues an attack on territory of player 1 and fails due to diplomacy
	Order* order24 = new Advance(5, engine->getGameMap()->getTerritory(2), engine->getGameMap()->getTerritory(3), player2);
	player2->issueOrder(order24);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP8: create and issue Bomb orders. attempt 1 and 2 will fail and 3 will succeed
	cout << endl << "===============================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 8      " << endl;
	cout << endl << "===============================" << endl;
	//creating bomb order 1: player 2 attempts to bomb neutral player but fails due to missing bomb card
	Order* order25 = new Bomb(player2, engine->getGameMap()->getTerritory(8));
	player2->issueOrder(order25);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating bomb order 2: player 2 now has bomb card in hands and attempts to bomb neutral player but fails because
	//he chose his territory by mistake
	//adding bomb card in hand
	Card* card11 = new Card(2);
	hand_p2->addCardToHand(card11);
	cout << endl << "Player has now added a BOMB  card in hand" << endl;
	Order* order26 = new Bomb(player2, engine->getGameMap()->getTerritory(2));
	player2->issueOrder(order26);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//create bomb order 3: player 2 has bomb card and chooses the right player. order succeeds
	Card* card12 = new Card(2);
	hand_p2->addCardToHand(card12);
	cout << endl << "Player has now added a BOMB  card in hand" << endl;
	Order* order27 = new Bomb(player2, engine->getGameMap()->getTerritory(8));
	player2->issueOrder(order27);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "===============================" << endl;
	cout << endl << "        END PART 4 DEMO        " << endl;
	cout << endl << "===============================" << endl;

	delete loader;
	delete map;
	delete engine;
	delete Player::common_deck;

}