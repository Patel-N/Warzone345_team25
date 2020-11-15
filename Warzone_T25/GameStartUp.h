#pragma once
#include "GameEngine.h"
#include <iostream>


class GameStartUp
{
public:

	//constructor
	 GameStartUp();
	GameStartUp(GameEngine* engine);

	//functions
	 void startUpPhase();

	 //attributes
	 GameEngine* gameEngine;
};

