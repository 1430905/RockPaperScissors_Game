#include "RPS_Tools.h"

RPS_Tools::RPS_Tools() {}

PLAY RPS_Tools::win(PLAY x) { 
	//returns what wins against PLAY x
	if (x == PLAY::Rock) {
		return PLAY::Paper;
	}
	else if (x == PLAY::Paper) {
		return PLAY::Scissors;
	}
	else {
		return PLAY::Rock;
	}
}

PLAY RPS_Tools::loss(PLAY x) {
	//Returns what loses agains PLAY x
	if (x == PLAY::Rock) {
		return PLAY::Scissors;
	}
	else if (x == PLAY::Paper) {
		return PLAY::Rock;
	}
	else {
		return PLAY::Paper;
	}
}

STATES RPS_Tools::WinOrLoss(PLAY user, PLAY opponent) { 
	//Returns if the game was a win, loss or draw
	if (user == opponent) {
		return STATES::Draw;
	}
	else if (user == win(opponent)) {
		return STATES::Win;
	}
	else {
		return STATES::Loss;
	}


}

double RPS_Tools::max(double a, double b, double c) { 
	//Returns the max between three double values
	double max = a;
	if (max < b) {
		max = b;
	}
	if (max < c) {
		max = c;
	}
	return max;
}



