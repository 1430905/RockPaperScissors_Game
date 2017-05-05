#pragma once
#include <iostream>
#include "RPS_Tools.h"
#include "History.h"

class OpponentPlayerManager {

private:
	int counter;
	RNG rng;
	RPS_Tools tools;
public:
	OpponentPlayerManager();
	PLAY play(int currentGame, History const &a,int type = 0);

};
