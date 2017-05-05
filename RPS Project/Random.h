#pragma once
#include "RPS_Player.h"
#include "RPS_Tools.h"
#include "History.h"
#include <iostream>

class Random : public RPS_Player {
private:
	RNG rng;
	RPS_Tools tools;
public:
	PLAY nextMove(History const &a, int currentGame);

};
