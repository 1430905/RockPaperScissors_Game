#pragma once
#include <iostream>
#include "RPS_Tools.h"
#include "History.h"

class RPS_Player {
public:
	 virtual PLAY nextMove(History const &a, int currentGame) = 0;
};
