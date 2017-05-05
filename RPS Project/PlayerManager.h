#pragma once
#include <vector>
#include <iostream>
#include "RPS_Player.h"
#include "Random.h"
#include "Stats.h"
#include "AntiHuman.h"
#include "History.h"


class PlayerManager {
	//What this is supposed to do:
	//1) Look at the Play field and evaluate if a change of Scheme is needed
	//2) Execute the decision
	//3) Play with the decision
	//4) return the value received from chosen play scheme
private:
	int randomBias;
    
	double confidence;
    
	double RandomOdds;// Random play odds
	double AAHPOdds; //Anti Average Human Player odds
	double StatsOdds;// Statistical play odds

	PLAY playRandom;
	PLAY stats;
	PLAY aahp;

	RPS_Tools tools;

	int currentScheme;

public:
	Random randomPlayingStyle; //Random Playing Style
	Stats StatisticalPlayer; //Stats Playing Style
	AntiHuman AntiHumanPlayer;
	PlayerManager();
	PlayerManager(int randomBias, double confidence);

	PLAY play(History const &a, int currentGame, PLAY lastOpponentMove = PLAY::Rock);

	int getCurrentScheme();

	void SchemeMod(int Scheme, int modifier);
};

