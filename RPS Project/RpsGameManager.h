#pragma once
#include "PlayerManager.h"
#include "RPS_Tools.h"
#include "OpponentPlayerManager.h"
#include <iostream>
#include <istream>
#include <fstream>
#include "History.h"

//(1-b) * p +- b

class RpsGameManager {

private:
int gameLength;					//Lenght of Full-Game
int currentGame;				//Game currently playing
int userScore;					//Score of the User
PlayerManager user;				//PlayerManager for User
OpponentPlayerManager opponent;	//PlayerManager for Opponent
RPS_Tools tools;				//RPS tools

PLAY userMove;		//User's move
PLAY opponentMove;	//Opponent's move

public:
	RpsGameManager();			//RPS Game Manager no-args Constructor
	RpsGameManager(int gameLength, int RandomBias, double Confidence);

	void run();
	void write(History a);
	int getGameLength();
	int getCurrentGame();
	void setGameLength(int gameLength);
	void updateScore(STATES GameStatus);
};
