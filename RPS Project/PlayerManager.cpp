#include "PlayerManager.h"
#include <iostream>

PlayerManager::PlayerManager() {
	this->currentScheme = 0;		//Initial Scheme (Placeholder since 0 is not a Scheme)

	this->RandomOdds = 0.333333;	//Initial odds
	this->AAHPOdds = 0.333333;		//
	this->StatsOdds = 0.333333;		//

	this->confidence = 0.05;		//Average confidence

	this->randomBias = 40;			//Average random bias
}

PlayerManager::PlayerManager(int randomBias, double confidence) {
	this->currentScheme = 0;

	this->RandomOdds = 0.333333;
	this->AAHPOdds = 0.333333;
	this->StatsOdds = 0.333333;

	this->confidence = confidence;

	this->randomBias = randomBias;
}


PLAY PlayerManager::play(History const &a, int currentGame, PLAY lastOpponentMove) {
	if (currentGame != 0) {	//If currentGame != 0, update the prob. for the playstyles
		if (playRandom == tools.win(lastOpponentMove)) {
			SchemeMod(1, 1);
		}
		else if(playRandom == tools.loss(lastOpponentMove)){
			SchemeMod(1, -1);
		}
		
		if (stats == tools.win(lastOpponentMove)) {
			SchemeMod(3, 1);
		}
		else if (stats == tools.loss(lastOpponentMove)) {
			SchemeMod(3, -1);
		}

		if (aahp == tools.win(lastOpponentMove)) {
			SchemeMod(2, 1);
		}
		else if (aahp == tools.loss(lastOpponentMove)) {
			SchemeMod(2, -1);
		}
	}
	
	playRandom = randomPlayingStyle.nextMove(a, currentGame);	//Play all three playstyles, but only 
	stats = StatisticalPlayer.nextMove(a, currentGame);			//Select one
	aahp = AntiHumanPlayer.nextMove(a, currentGame);			//

	std::cout << "\nRandom Odds : " << RandomOdds;				//Printing odds for user
	std::cout << "\nAAHP Odds : " << AAHPOdds;					//
	std::cout << "\nStats Odds : " << StatsOdds << "\n";		//

	if (currentGame < randomBias) {								//If the currentGame is under the 
		currentScheme = 1;										//Random bias, play Random
		return playRandom;										//
	}															//
	
	else {
		double max = tools.max(RandomOdds, AAHPOdds, StatsOdds);// Finds the highest prob. playstyle and plays it.
		if (max == RandomOdds) {								//
			currentScheme = 1;									//
			return playRandom;									//
		}														//
		else if (max == AAHPOdds) {								//
			currentScheme = 2;									//
			return aahp;										//
		}														//
		else {													//
			currentScheme = 3;									//
			return stats;										//
		}														//

	}
	
}

int PlayerManager::getCurrentScheme() { //Returns the Current Scheme
	return currentScheme;
}

void PlayerManager::SchemeMod(int Scheme, int modifier) { 
	//Updates the Values and makes them higher than 0%, lower than 80% and tries 
	//to make them all sum under 100%
	if (Scheme == 1) {//Scheme 1 = Random
		if (modifier == 1) {
			double temp = RandomOdds;
			RandomOdds = RandomOdds*(1 - confidence) + confidence;
			double temp2 = (temp - RandomOdds) / 2;

			AAHPOdds += temp2;
			StatsOdds += temp2;
		}
		else {
			double temp = AAHPOdds;
			AAHPOdds = AAHPOdds*(1 - confidence) + (confidence);
			double temp2 = (temp - AAHPOdds) / 2;
			RandomOdds += (temp2);
			StatsOdds += (temp2);

			temp = StatsOdds;// Scheme 3 = Statistical play
			StatsOdds = StatsOdds*(1 - confidence) + (confidence);
			temp2 = (temp - StatsOdds) / 2;
			AAHPOdds += (temp2);
			RandomOdds += (temp2);
		}
	}
	else if (Scheme == 2) {// Scheme 2 = Anti human play
		if (modifier == 1) {
		double temp = AAHPOdds;
		AAHPOdds = AAHPOdds*(1 - confidence) + confidence;
		double temp2 = (temp - AAHPOdds)/2;

		RandomOdds += (temp2);
		StatsOdds += (temp2);
		}
		else {
			double temp = StatsOdds;// Scheme 3 = Statistical play
			StatsOdds = StatsOdds*(1 - confidence) + (confidence);
			double temp2 = (temp - StatsOdds) / 2;
			AAHPOdds += (temp2);
			RandomOdds += (temp2);

			temp = RandomOdds;
			RandomOdds = RandomOdds*(1 - confidence) + (confidence);
			temp2 = (temp - RandomOdds) / 2;
			StatsOdds += (temp2);
			AAHPOdds += (temp2);
		}
		
	}
	else {
		if (modifier == 1) {
			double temp = StatsOdds;// Scheme 3 = Statistical play
			StatsOdds = StatsOdds*(1 - confidence) + (confidence);
			double temp2 = (temp - StatsOdds) / 2;
			AAHPOdds += (temp2);
			RandomOdds += (temp2);
		}
		else {
			double temp = AAHPOdds;
			AAHPOdds = AAHPOdds*(1 - (confidence)) + (confidence);
			double temp2 = (temp - AAHPOdds) / 2;
			StatsOdds += (temp2);
			RandomOdds += (temp2);

			temp = RandomOdds;
			RandomOdds = RandomOdds*(1 - (confidence)) + (confidence);
			temp2 = (temp - RandomOdds) / 2;
			StatsOdds += (temp2);
			AAHPOdds += (temp2);
		}
	}

	double temp2;

	if (StatsOdds < 0) {
		temp2 = StatsOdds;
		AAHPOdds -= temp2 / 2;
		RandomOdds -= temp2 / 2;
		StatsOdds = 0;
	}
	if (AAHPOdds < 0) {
		temp2 = AAHPOdds;
		RandomOdds -= temp2 / 2;
		StatsOdds -= temp2 / 2;
		AAHPOdds = 0;
	}
	if (RandomOdds < 0) {
		temp2 = RandomOdds;
		StatsOdds -= temp2 / 2;
		AAHPOdds -= temp2 / 2;
		RandomOdds = 0;
	}
	if (StatsOdds > 0.8) {
		temp2 = StatsOdds;
		StatsOdds = 0.8;
		temp2 -= StatsOdds;
		RandomOdds += temp2/2;
		AAHPOdds += temp2/2;
	}
	if (RandomOdds > 0.8) {
		temp2 = RandomOdds;
		RandomOdds = 0.8;
		temp2 -= RandomOdds;
		StatsOdds += temp2/2;
		AAHPOdds += temp2/2;
	}
	if (AAHPOdds > 0.8) {
		temp2 = AAHPOdds;
		AAHPOdds = 0.8;
		temp2 -= AAHPOdds;
		StatsOdds += temp2/2;
		RandomOdds += temp2/2;
	}
	if (AAHPOdds + RandomOdds + StatsOdds > 1) {
		temp2 = AAHPOdds + RandomOdds + StatsOdds - 1;
		AAHPOdds -= temp2 / 3;
		RandomOdds -= temp2 / 3;
		StatsOdds -= temp2 / 3;
		if (StatsOdds < 0) {
			temp2 = StatsOdds;
			AAHPOdds -= temp2 / 2;
			RandomOdds -= temp2 / 2;
			StatsOdds = 0;
		}
		if (AAHPOdds < 0) {
			temp2 = AAHPOdds;
			RandomOdds -= temp2 / 2;
			StatsOdds -= temp2 / 2;
			AAHPOdds = 0;
		}
		if (RandomOdds < 0) {
			temp2 = RandomOdds;
			StatsOdds -= temp2 / 2;
			AAHPOdds -= temp2 / 2;
			RandomOdds = 0;
		}
	}

}
