#pragma once
#include <iostream>
#include "RNG.h"

enum PLAY { Rock, Paper, Scissors };
enum STATES { Win, Loss, Draw };

class RPS_Tools{
public:
	RPS_Tools();
	PLAY win(PLAY x);
	PLAY loss(PLAY x);
	STATES WinOrLoss(PLAY user, PLAY opponent);

	double max(double a, double b, double c);

};
