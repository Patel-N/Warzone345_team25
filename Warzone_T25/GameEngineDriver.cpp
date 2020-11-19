#include "GameEngine.h"
#include "MapLoader.h"


void part_3::start() {

	MapLoader* loader = new MapLoader();
	Map* map = (loader->generateMap("./MapFiles/canada.map"));
	GameEngine* engine = new GameEngine(map);
	Player* player1 = new Player(1, "Yasser");
	Player* player2 = new Player(2, "Neil");

	//Adding cards
	Deck* d = new Deck();
	Player::common_deck = d;
	Card* c1 = new Card(1);
	Card* c2 = new Card(2);
	Card* c3 = new Card(3);
	Card* c4 = new Card(4);
	Card* c5 = new Card(5);
	Player::common_deck->addCardToDeck(c1);
	Player::common_deck->addCardToDeck(c2);
	Player::common_deck->addCardToDeck(c3);
	Player::common_deck->addCardToDeck(c4);
	Player::common_deck->addCardToDeck(c5);

	//Setup hand
	Hand* h1 = new Hand();
	Hand* h2 = new Hand();
	player1->setPlayerHand(h1);
	player2->setPlayerHand(h2);


	engine->addPlayer(player1);
	engine->addPlayer(player2);

	//cont 1
	map->assignOccupantToTerritory(1, player1);
	Territory* territory = map->getTerritory(1);
	player1->assignTerritoryToPlayer(territory);
	map->assignOccupantToTerritory(2, player1);
	Territory* territory2 = map->getTerritory(2);
	player1->assignTerritoryToPlayer(territory2);
	map->assignOccupantToTerritory(3, player1);
	Territory* territory3 = map->getTerritory(3);
	player1->assignTerritoryToPlayer(territory3);
	map->assignOccupantToTerritory(4, player1);
	Territory* territory4 = map->getTerritory(4);
	player1->assignTerritoryToPlayer(territory4);
	map->assignOccupantToTerritory(5, player1);
	Territory* territory5 = map->getTerritory(5);
	player1->assignTerritoryToPlayer(territory5);

	//cont 2
	map->assignOccupantToTerritory(6, player1);
	Territory* territory6 = map->getTerritory(6);
	player1->assignTerritoryToPlayer(territory6);
	territory6->setNumArmies(25);
	map->assignOccupantToTerritory(7, player1);
	Territory* territory7 = map->getTerritory(7);
	player1->assignTerritoryToPlayer(territory7);
	territory7->setNumArmies(13);
	map->assignOccupantToTerritory(8, player1);
	Territory* territory8 = map->getTerritory(8);
	player1->assignTerritoryToPlayer(territory8);
	map->assignOccupantToTerritory(9, player1);
	Territory* territory9 = map->getTerritory(9);
	player1->assignTerritoryToPlayer(territory9);
	territory9->setNumArmies(10);


	map->assignOccupantToTerritory(10, player2);
	Territory* territory10 = map->getTerritory(10);
	player2->assignTerritoryToPlayer(territory10);
	territory10->setNumArmies(5);



	engine->mainGameLoop();
}