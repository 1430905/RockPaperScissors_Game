#include <iostream>
#include "Stats.h"

Stats::Stats() {

	this->confidence = 0.05;

	this->drawMinus = 0.333333;
	this->drawPlus = 0.333333;
	this->drawStay = 0.333333;

	this->winMinus = 0.333333;
	this->winPlus = 0.333333;
	this->winStay = 0.333333;

	this->lossMinus = 0.333333;
	this->lossPlus = 0.333333;
	this->lossStay = 0.333333;
}

Stats::Stats(double confidence) {
	this->confidence = confidence;

	this->drawMinus = 0.333333;
	this->drawPlus = 0.333333;
	this->drawStay = 0.333333;

	this->winMinus = 0.333333;
	this->winPlus = 0.333333;
	this->winStay = 0.333333;

	this->lossMinus = 0.333333;
	this->lossPlus = 0.333333;
	this->lossStay = 0.333333;
}

PLAY Stats::nextMove(History const &a, int currentGame) {
	if (currentGame < 2) {			//Stats cannot have any info if there is no history yet : will play randomly
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
		update(a, currentGame);			//Updates the probabilities

		STATES lastGame = a.WinLossHistory[currentGame - 1];	//Finds which state is to used

		if (lastGame == STATES::Win) { // Finds which prob. in Win is the highest and returns it
			double max = tools.max(winMinus, winPlus, winStay);
			if (max == winMinus) {
				return tools.win(tools.loss(a.OpponentHistory[currentGame - 1]));
			}
			else if (max == winPlus) {
				return tools.win(tools.win(a.OpponentHistory[currentGame - 1]));
			}
			else {
				return tools.win(a.OpponentHistory[currentGame - 1]);
			}
		}
		else if (lastGame == STATES::Loss) {//Finds which prob. in Loss is the highest and returns it
			double max = tools.max(lossMinus, lossPlus, lossStay);
			if (max == lossMinus) {
				return tools.win(tools.loss(a.OpponentHistory[currentGame - 1]));
			}
			else if (max == lossPlus) {
				return tools.win(tools.win(a.OpponentHistory[currentGame - 1]));
			}
			else {
				return tools.win(a.OpponentHistory[currentGame - 1]);
			}
		}
		else {	//Find which probability in draw is the highest and plays it
			double max = tools.max(drawMinus, drawPlus, drawStay);
			if (max == drawMinus) {
				return tools.win(tools.loss(a.OpponentHistory[currentGame - 1]));
			}
			else if (max == drawPlus) {
				return tools.win(tools.win(a.OpponentHistory[currentGame - 1]));
			}
			else {
				return tools.win(a.OpponentHistory[currentGame - 1]);
			}
		}
	}

}

void Stats::update(History const &a, int currentGame) {
PLAY currentMin2 = a.OpponentHistory[currentGame - 2];
		PLAY currentMin1 = a.OpponentHistory[currentGame - 1];

		STATES state = a.WinLossHistory[currentGame - 2];

		int current;
		if (currentMin1 == tools.win(currentMin2)) {
			current = 1; //Opponent did +1 (Took what won against his last hand)
		}
		else if (currentMin1 == tools.loss(currentMin2)) {
			current = -1;//Opponent did -1 (Took what lost against his last hand)
		}
		else {
			current = 0;//Opponent did 0 (Stood)
		}

		if (state == STATES::Win) {
			if (current == 1) { //Increases Win Plus
				changeStats(winPlus, winMinus, winStay);
			}
			else if (current == -1) {//Increases Win Minus
				changeStats(winMinus, winPlus, winStay);
			}
			else {//Increases Win Stay
				changeStats(winStay, winPlus, winMinus);
			}
		}
		else if (state == STATES::Loss) {
			if (current == 1) {//Increases Loss Plus
				changeStats(lossPlus, lossMinus, lossStay);
			}
			else if (current == -1) {//Increases Loss Minus
				changeStats(lossMinus, lossPlus, lossStay);
			}
			else {//Increases Loss Stay
				changeStats(lossStay, lossPlus, lossMinus);
			}
		}
		else {
			if (current == 1) {//Increases draw Plus
				changeStats(drawPlus, drawMinus, drawStay);
			}
			else if (current == -1) {//Increases Draw Loss
				changeStats(drawMinus, drawPlus, drawStay);
			}
			else {//Increases Draw Stay
				changeStats(drawStay, drawPlus, drawMinus);
			}
		}

		if (drawMinus + drawPlus + drawStay > 1) {
			double temp = drawMinus + drawPlus + drawStay - 1;
			drawMinus -= temp / 3;
			drawPlus -= temp / 3;
			drawStay -= temp / 3;
		}

		if (winMinus + winPlus + winStay > 1) {
			double temp = winMinus + winPlus + winStay - 1;
			winMinus -= temp / 3;
			winPlus -= temp / 3;
			winStay -= temp / 3;
		}
		if(lossMinus + lossPlus + lossStay > 1) {
			double temp = lossMinus + lossPlus + lossStay - 1;
			lossMinus -= temp / 3;
			lossPlus -= temp / 3;
			lossStay -= temp / 3;
		}
}

void Stats::changeStats(double &chosen, double &other1, double &other2) {

		double temp = chosen;
		chosen = (1 - confidence)*chosen + confidence; //Probability equation
		double temp2 = (temp - chosen) / 2; //Finds difference between new and old prob. and divides it by 2
		other1 += temp2; //Adds the neg. half of the difference
		other2 += temp2; //Adds the neg. half of the difference

		if (other1 < 0) {		// Makes the probabilities under 0, zero
			temp2 = other1;		// And equalises everything
			chosen -= temp2/2;	//
			other2 -= temp2/2;	//
			other1 = 0;			//
		}						//
		if (other2 < 0) {		//
			temp2 = other2;		//
			chosen -= temp2 / 2;//
			other1 -= temp2 / 2;//
			other2 = 0;			//
		}						//
		if (chosen < 0) {		//
			temp2 = chosen;		//
			other2 -= temp2 / 2;//
			other1 -= temp2 / 2;//
			chosen = 0;			//
		}						//
		if (chosen > 0.8) {			//Makes the probabilities higher than 80%, 80%
			temp2 = chosen;			//And equalises everything
			chosen = 0.8;			//
			temp2 -= chosen;		//
			other1 += temp2/2;		//
			other2 += temp2/2;		//
		}							//
		if (other2 > 0.8) {			//
			temp2 = other2;			//
			other2 = 0.8;			//
			temp2 -= other2;		//
			other1 += temp2/2;		//
			chosen += temp2/2;		//
		}							//
		if (other1 > 0.8) {			//
			temp2 = other1;			//
			other1 = 0.8;			//
			temp2 -= other1;		//
			chosen += temp2/2;		//
			other2 += temp2/2;		//
		}							//
							
}