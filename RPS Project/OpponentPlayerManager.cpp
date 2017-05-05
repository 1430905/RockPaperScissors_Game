#include "OpponentPlayerManager.h"

OpponentPlayerManager::OpponentPlayerManager() {
	this->counter = 0;
}

PLAY OpponentPlayerManager::play(int currentGame, History const &a, int type) {
	if (type == 0) {		//if Type == 0, play randomly
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
	else if (type == 1) { // If Type == 1, play only Rock
		return PLAY::Rock;
	}
	else if (type == 2) { // If Type == 2, play only Rock, then Paper, then Scissors
		if (counter == 0) {
			counter++;
			return PLAY::Rock;
		}
		else if (counter == 1) {
			counter++;
			return PLAY::Paper;
		}
		else {
			counter = 0;
			return PLAY::Scissors;
		}
	}
	else if(type == 3){ // If type == 3, Play Average human strategy
		STATES lastGame;
		if (currentGame == 0) {
			lastGame = STATES::Draw;
		}
		else {
			lastGame = a.WinLossHistory[currentGame - 1];
		}

		if (lastGame == STATES::Win) {
			return tools.win(a.UserHistory[currentGame - 1]);
		}
		else if (lastGame == STATES::Loss) {
			return a.OpponentHistory[currentGame - 1];
		}
		else {
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
	else if (type == 4) {
		if (counter == 0) {
			counter++;
			return PLAY::Rock;
		}
		else {
			counter = 0;
			return PLAY::Paper;
		}
	}
	else { //If type = 5 or other		Input value with Cin for player
		int input;
		std::cout << "Enter your value : (0 : Rock, 1 : Paper, 2: Scissors): ";
		std::cin >> input;
		if (input == 0) {
			return PLAY::Rock;
		}
		else if (input == 1) {
			return PLAY::Paper;
		}
		else {
			return PLAY::Scissors;
		}
	}
}