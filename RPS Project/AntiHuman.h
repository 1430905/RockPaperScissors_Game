#pragma once
#include "RPS_Tools.h"
#include "RPS_Player.h"
#include "History.h"
#include <iostream>

class AntiHuman : public RPS_Player {

private:
	RNG rng;
	RPS_Tools tools;
public:
	PLAY nextMove(History const &a, int currentGame);


};
