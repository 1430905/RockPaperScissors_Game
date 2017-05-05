#include "AntiHuman.h"
#include <iostream>
#include <vector>

//I found this Anti human strategy while doing research on the web.
// They are a mathematics youtube channel called "Numberphile" that I follow.
//
// Here : https://youtu.be/rudzYPHuewc is the link to the video
// As well as basing my Draw case on what we had in the document

PLAY AntiHuman::nextMove(History const &a, int currentGame) {
	if (currentGame == 0) {		//If its the first game, play random
		int random = rng.getRandom(0, 2);

		if (random == 0) {
			return PLAY::Rock;
		}
		else if (random == 1) {
			return PLAY::Paper;
		}
		else {
			return PLAY::Scissors;
		}
	}
	else {
		if (a.WinLossHistory[currentGame - 1] == STATES::Win) { 
			//If you just won, play what your opponent just played
			return a.OpponentHistory[currentGame - 1];
		}
		else if (a.WinLossHistory[currentGame - 1] == STATES::Loss) { 
			// If you just lost, play what would lose gainst what you just played
			return tools.loss(a.UserHistory[currentGame - 1]);
		}
		else {//If its a draw, play randomly
			int random = rng.getRandom(0, 2);

			if (random == 0) {
				return PLAY::Rock;
			}
			else if (random == 1) {
				return PLAY::Paper;
			}
			else {
				return PLAY::Scissors;
			}
		}
	}
}

