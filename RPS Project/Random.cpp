#include "Random.h"
#include <iostream>

	PLAY Random::nextMove(History const &a, int currentGame) {
		//Return a random move
		int random = rng.getRandom(0,2);

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
