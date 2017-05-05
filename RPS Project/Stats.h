#pragma once
#include <vector>
#include <iostream>
#include "RPS_Tools.h"
#include "RPS_Player.h"
#include "History.h"

class Stats : public RPS_Player{
private:
	
	RNG rng;

	
	double confidence;

	RPS_Tools tools;

public:
	double winMinus;
	double winPlus;
	double winStay;

	double lossMinus;
	double lossPlus;
	double lossStay;

	double drawMinus;
	double drawPlus;
	double drawStay;

	Stats();
	Stats(double confidence);
	PLAY nextMove(History const &a, int currentGame);

	void changeStats(double &chosen, double &other1, double &other2);
	void update(History const &a, int currentGame);
};
