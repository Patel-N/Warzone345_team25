
#include <iostream>
#include"Cards.h"
#include"Map.h"
#include "MapLoader.h"
#include"Player.h"
#include"GameEngine.h"

void part_4::start() {
	//creating game engine, creating map, loading canada map
	MapLoader* loader = new MapLoader();
	Map* map = (loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);
	//creating deck and initializing static player variable common_deck
	Deck* deck = new Deck();
	Player::common_deck = deck;
	Card* card1 = new Card(1);
	Card* card2 = new Card(2);
	Card* card3 = new Card(3);
	Card* card4 = new Card(4);
	Card* card5 = new Card(5);
	deck->addCardToDeck(card1);
	deck->addCardToDeck(card2);
	deck->addCardToDeck(card3);
	deck->addCardToDeck(card4);
	deck->addCardToDeck(card5);
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
	cout << endl << "=======================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 1:DEPLOY DEMO      " << endl;
	cout << endl << "=======================================" << endl;
	//DEMO STEP1: create and issue deploy orders. player 1 and 2 orders will succeed. player 3 and 4 will fail:
	//DEPLOY DOES NOT REQUIRE A CARD
	//player 1 successful deploy
	Order* order1 = new Deploy(10, engine->getGameMap()->getTerritory(1), player1);
	player1->issueOrder(order1);
	//player 2 successful deploy
	Order* order2 = new Deploy(10, engine->getGameMap()->getTerritory(2), player2);
	player2->issueOrder(order2);
	Order* order3 = new Deploy(10, engine->getGameMap()->getTerritory(3), player3);//attempt at deploying 10 when only 5 is available
	player3->issueOrder(order3);
	//player 4 fail[territory does not belong to player] deploy order attempt
	Order* order4 = new Deploy(10, engine->getGameMap()->getTerritory(3), player4);//territory 3 belongs to player 3
	player4->issueOrder(order4);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP 2: deploying all armies to begin game
	cout << endl << "=========================================================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 2:Transition part. deploying remaining armies    " << endl;
	cout << endl << "=========================================================================" << endl;
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
	cout << endl << "=========================================================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 3 :Transition part.Assigning new Territories     " << endl;
	cout << endl << "=========================================================================" << endl;
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
	cout << endl << "============================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 4:ADVANCE DEMO      " << endl;
	cout << endl << "============================================" << endl;
	//creating advance order1: Player 1 will move 7 armies from 4 to 7 and will succeed. 
	Order* order9 = new Advance(7, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(7), player1);
	player1->issueOrder(order9);
	//creating advance order2: Player 3 will advance armies from territory 3 to territory 4 creating an attack. he will attack with 9 armies
	//order will execute successfully. outcome to be determined.
	Order* order10 = new Advance(9, engine->getGameMap()->getTerritory(3), engine->getGameMap()->getTerritory(4), player3);
	player3->issueOrder(order10);
	//creating advance order3: Player 1 will try to advance armies from territory 4 to territory 8. will fail because source territory 
	//does not belong to issuing player
	Order* order11 = new Advance(5, engine->getGameMap()->getTerritory(8), engine->getGameMap()->getTerritory(7), player1);
	player1->issueOrder(order11);
	//create advance order4: Player 3 will now try to attack territory 8 but will fail because it is not adjacent
	Order* order12 = new Advance(9, engine->getGameMap()->getTerritory(4), engine->getGameMap()->getTerritory(8), player3);
	player3->issueOrder(order12);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP5: create and issue airlift orders. order 1 and 2 will fail, 3,4 will succeed.
	cout << endl << "==============================================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 5:AIRLIFT DEMO [ALSO CARDS DEMO]      " << endl;
	cout << endl << "==============================================================" << endl;
	//creating airlift order 2: player 1 will attempt at doing airlift from territory 8- which does not belong to him. attack will fail
	//adding airlift card to hand
	Order* order14 = new Airlift(10, engine->getGameMap()->getTerritory(8), engine->getGameMap()->getTerritory(4), player1);
	player1->issueOrder(order14);
	//creating airlift order 3: player 1 will now to attack from territory 7 to 3 by doing an airlift.attack will succeed
	//adding airlift card to hand
	engine->getGameMap()->getTerritory(3)->setNumArmies(0);//set armies to 0 to allow player 1 to take over territory
	Order* order15 = new Airlift(10, engine->getGameMap()->getTerritory(7), engine->getGameMap()->getTerritory(3), player1);
	player1->issueOrder(order15);
	//creating airlift order 4: player 1 will airlift from territory 1 to territory 3. Attack will succeed but player won't gain a card
	engine->getGameMap()->getTerritory(2)->setNumArmies(0);//set armies to 0 to allow player 1 to take over territory
	Order* order16 = new Airlift(7, engine->getGameMap()->getTerritory(1), engine->getGameMap()->getTerritory(2), player1);
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
	cout << endl << "=============================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 6:BLOCKADE DEMO      " << endl;
	cout << endl << "=============================================" << endl;
	//creating blockade order 2: player 2 is able to use blockade card but territory does not belong to him
	Order* order18 = new Blockade(player4, engine->getGameMap()->getTerritory(1));
	player4->issueOrder(order18);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating blockade order 3: player 2 is able to use blockade card and blockade is successful
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
	cout << endl << "==============================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 7:NEGOTIATE DEMO      " << endl;
	cout << endl << "==============================================" << endl;
	//DEMO STEP7: create and issue Negotiate orders. 2 will fail, order 3 will succeed. then attempt at attacking by both players in the negotiation fails
	//creating negotiate order 2: a card is added in the player2's hand, but player 2 issues a negotiation with himself
	Order* order21 = new Negotiate(player2, player2);
	player2->issueOrder(order21);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//creating negotiate order 3: player 1 now issues negotiate order and it succeeds
	Order* order22 = new Negotiate(player1, player2);
	player1->issueOrder(order22);
	//adding territory to player 2 to demonstrate with no fail the diplomacy
	engine->getGameMap()->assignOccupantToTerritory(5, player2);
	player2->assignTerritoryToPlayer(engine->getGameMap()->getTerritory(5));
	//player 1 issues attack on territory of player 2 and fails due to diplomacy
	Order* order23 = new Advance(5, engine->getGameMap()->getTerritory(7), engine->getGameMap()->getTerritory(5),player1);
	player1->issueOrder(order23);
	//player 2 issues an attack on territory of player 1 and fails due to diplomacy
	Order* order24 = new Advance(5, engine->getGameMap()->getTerritory(5), engine->getGameMap()->getTerritory(7), player2);
	player2->issueOrder(order24);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP8: create and issue Bomb orders. attempt 1 and 2 will fail and 3 will succeed
	cout << endl << "=========================================" << endl;
	cout << endl << "    PART4 DEM0: SUBPART 8:BOMB DEMO      " << endl;
	cout << endl << "=========================================" << endl;
	//creating bomb order 2: player 2 now has bomb card in hands and attempts to bomb neutral player but fails because
	//he chose his territory by mistake
	Order* order26 = new Bomb(player2, engine->getGameMap()->getTerritory(2));
	player2->issueOrder(order26);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//create bomb order 3: player 2 has bomb card and chooses the right player. order succeeds
	Order* order27 = new Bomb(player2, engine->getGameMap()->getTerritory(8));
	player2->issueOrder(order27);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	//DEMO STEP9: create and issue Reinforcement orders. attempt 1 will work and 2 will fail
	cout << endl << "==========================================" << endl;
	cout << endl << " PART4 DEM0: SUBPART 9:REINFORCEMENT DEMO    " << endl;
	cout << endl << "==========================================" << endl;

	//create reinforcement order 2: will succeed because player has the card
	Order* order29 = new Reinforcement(player2);
	player2->issueOrder(order29);
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "===================================" << endl;
	cout << endl << "  DISPLAYING STARTS AFTER PART 9   " << endl;
	cout << endl << "===================================" << endl;
	cout << endl << "TERRITORIES IN DEMO" << endl;
	cout << endl << "=============================" << endl;
	cout << *engine->getGameMap()->getTerritory(1) << endl;
	cout << *engine->getGameMap()->getTerritory(2) << endl;
	cout << *engine->getGameMap()->getTerritory(3) << endl;
	cout << *engine->getGameMap()->getTerritory(4) << endl;
	cout << *engine->getGameMap()->getTerritory(7) << endl;
	cout << *engine->getGameMap()->getTerritory(8) << endl;
	//DEMO STEP10: create and issue orders in random orders and display how they get executed  in priority
	//adding armies in player 1 and 2 pool:
	player1->setArmyToBePlaced(10);
	player2->setArmyToBePlaced(15);
	Order* order30 = new Airlift(2, engine->getGameMap()->getTerritory(1), engine->getGameMap()->getTerritory(7), player1);
	Order* order31 = new Blockade(player2, engine->getGameMap()->getTerritory(2));
	Order* order32 = new Deploy(10, engine->getGameMap()->getTerritory(1), player1);
	Order* order33 = new Deploy(15, engine->getGameMap()->getTerritory(2), player2);
	Order* order34 = new Deploy(8, engine->getGameMap()->getTerritory(1), player1);
	Order* order35 = new Bomb(player2,engine->getGameMap()->getTerritory(1));
	Order* order36 = new Negotiate(player1, player2);
	Order* order37 = new Reinforcement(player2);
	player1->issueOrder(order30);
	player2->issueOrder(order31);
	player1->issueOrder(order32);
	player2->issueOrder(order33);
	player1->issueOrder(order34);
	player2->issueOrder(order35);
	player1->issueOrder(order36);
	player2->issueOrder(order37);
	cout << endl << "==================================================" << endl;
	cout << endl << " PART4 DEM0: SUBPART 10:PRE EXECUTION ORDER LISTS " << endl;
	cout << endl << "==================================================" << endl;
	cout << endl << "Player " << player1->getPlayerId() << " List: " << endl;
	cout << *player1->getOrderList();
	cout << endl << "Player " << player2->getPlayerId() << " List: " << endl;
	cout << *player2->getOrderList();
	engine->executeOrdersPhase();//after this function call, all orders are deleted
	cout << endl << "==========================================" << endl;
	cout << endl << " PART4 DEM0: SUBPART 10:ORDERLIST DEMO    " << endl;
	cout << endl << "==========================================" << endl;
	cout << endl << "===============================" << endl;
	cout << endl << "        END PART 4 DEMO        " << endl;
	cout << endl << "===============================" << endl;
	cout << endl << "DEMO ENGINE COPY CONSTRUCTOR" << endl;

	delete loader;
	delete map;
	delete engine;
	delete Player::common_deck;

}