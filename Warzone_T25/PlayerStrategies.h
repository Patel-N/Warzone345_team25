#pragma once
#include "Player.h"
#include <algorithm>
class PlayerStrategies {
	void  issueOrder();

};

class HumanPlayerStrategy: PlayerStrategies {};

class AggressivePlayerStrategy : PlayerStrategies {};

class BenevolentPlayerStrategy : PlayerStrategies {};

class NeutralPlayerStrategy : PlayerStrategies {};

