#include "RpsGameManager.h"
#include <iostream>

RpsGameManager::RpsGameManager() {
	this->gameLength = 1000;
	this->currentGame = 0;
	this->userScore = 0;
	this->userMove = PLAY::Rock;
	this->opponentMove = PLAY::Rock;
	this->user = PlayerManager(100, 0.05);
}

RpsGameManager::RpsGameManager(int gameLength, int RandomBias, double Confidence) {
	this->gameLength = gameLength;
	this->currentGame = 0;
	this->userScore = 0;
	this->userMove = PLAY::Rock;
	this->opponentMove = PLAY::Rock;
	this->user = PlayerManager(RandomBias, Confidence);
}

void RpsGameManager::run() {
	History a;
	int wins = 0;
	int losses = 0;
	int draws = 0;
	int opponentType = 2;
	for (int i = 0; i < gameLength; i++) { //Loop to accomplish the number of games given
		
		if (i == 0) {
			userMove = user.play(a,i);				//User requires Last opponent move, however, none exist at turn 0, then -> default
			opponentMove = opponent.play(i,a,opponentType);	//Opponent move : (i,a,0) -> Random
													//(i,a,1) -> RRRR...
													//(i,a,2) -> RPSRPS...
													//(i,a,3) -> Average Human
													//(i,a,4) -> RPRPRP...
													//(i,a,5 or other) -> Actual play
													//Modify X {(i,a,X)} to change the opponent type
													//DONT FORGET TO CHANGE THIS IF YOU WANT TO CHANGE OPPONENT TYPE
		}
		else {
			userMove = user.play(a,i,a.OpponentHistory[i-1]); //Uses opponent's last move
			opponentMove = opponent.play(i,a,opponentType);   //Same as before
												   //DONT FORGET TO CHANGE THIS IF YOU WANT TO CHANGE OPPONENT TYPE
		}
		STATES GameStatus = tools.WinOrLoss(userMove, opponentMove); //Determines if game was won or lost or draw

		updateScore(GameStatus); //Updates the score based on previous calculation

		a.OpponentHistory.push_back(opponentMove);		//Add Information to History
		a.UserHistory.push_back(userMove);				//
		a.Score.push_back(userScore);					//
		a.WinLossHistory.push_back(GameStatus);			//
		a.Scheme.push_back(user.getCurrentScheme());	//

		currentGame++;									//Increment currentGame
		std::cout << "\n" << currentGame << "." ;							//Prints the information for the user
		std::cout << "\nSchemeUsed: " << user.getCurrentScheme();			//
		std::cout << "\nAI move : ";										//
		if (userMove == PLAY::Rock) {										//
			std::cout << "Rock";											//
		}																	//
		else if (userMove == PLAY::Paper) {									//
			std::cout << "Paper";											//
		}																	//
		else {																//
			std::cout << "Scissors";										//
		}																	//
		std::cout << "\nPLAYER move : ";									//
		if (opponentMove == PLAY::Rock) {									//
			std::cout << "Rock";											//
		}																	//
		else if (opponentMove == PLAY::Paper) {								//
			std::cout << "Paper";											//
		}																	//
		else {																//
			std::cout << "Scissors";										//
		}																	//
		std::cout << "\nResult: ";											//
			if (GameStatus == STATES::Win) {								//
				std::cout << "AI : WIN / PLAYER LOSS";						//
				wins++;														//
			}																//
			else if (GameStatus == STATES::Loss) {							//
				std::cout << "AI : LOSS / PLAYER WIN";						//
				losses++;													//
			}																//
			else {															//
				std::cout << "DRAW!";										//
				draws++;													//
			}																//
		std::cout << "\n";													//
																			//
		if (user.getCurrentScheme() == 3) {									//
			if (GameStatus == STATES::Win) {								//
				std::cout << "\n+1 : " << user.StatisticalPlayer.winPlus;	//
				std::cout << "\n-1 : " << user.StatisticalPlayer.winMinus;	//
				std::cout << "\n0 : " << user.StatisticalPlayer.winStay;	//
			}																//
			if (GameStatus == STATES::Loss) {								//
				std::cout << "\n+1 : " << user.StatisticalPlayer.lossPlus;	//
				std::cout << "\n-1 : " << user.StatisticalPlayer.lossMinus;	//
				std::cout << "\n0 : " << user.StatisticalPlayer.lossStay;	//
			}																//
			if (GameStatus == STATES::Draw) {								//
				std::cout << "\n+1 : " << user.StatisticalPlayer.drawPlus;	//
				std::cout << "\n-1 : " << user.StatisticalPlayer.drawMinus;	//
				std::cout << "\n0 : " << user.StatisticalPlayer.drawStay;	//
			}																//
		}																	//
	}																		//
	std::cout << "\nFinal Result: " << a.Score[currentGame - 1];			//
	std::cout << "\n";														//
	std::cout << "\nWins : " << wins;										//
	std::cout << "\nLosses : " << losses;									//
	std::cout << "\nDraws : " << draws << endl;								//
	write(a);	//Writes the final results in the .csv files
}

int RpsGameManager::getGameLength() { //Returns the length of the game
	return gameLength;
}

void RpsGameManager::setGameLength(int gameLength) { //Lets you set the length of the game
	this->gameLength = gameLength;
}

void RpsGameManager::write(History a) {		// Writes the files in the format illustrated in the document
	char* OpponentP = "OpponentPlays.csv";	// Links for the files
	char* UserP = "UserPlays.csv";			//
	char* S1 = "Scheme1.csv";				//
	char* S2 = "Scheme2.csv";				//
	char* S3 = "Scheme3.csv";				//
	char* Score = "Score.csv";				//
	char* Results = "SchemesChosen.csv";	//

	int currentUserScheme = user.getCurrentScheme();
	
	std::ofstream out;

	//////////////////////////Opponent Plays/////////////////////////////////////////////

	
	out.open(OpponentP);

	if (!out) {
		std::cout << "file " << OpponentP << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			out << a.OpponentHistory[i];

		}
		else {
			out << "," << a.OpponentHistory[i];
		}
	}
	out.close();
	
	
	/////////////////////User Plays///////////////////////////////////////////

		out.open(UserP);

	if (!out) {
		std::cout << "file " << UserP << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			out << a.UserHistory[i];

		}
		else {
			out << "," << a.UserHistory[i];
		}
	}
	out.close();
	
	/////////////////////Score/////////////////////////////////////////////////

		out.open(Score);
		std::cout << "out opened\n";

	if (!out) {
		std::cout << "file " << Score << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			out << a.Score[i];
		}
		else {
			out << "," << a.Score[i];
		}
	}
	out.close();

	
	/////////////////Result Record///////////////////////////////////////////////
		out.open(Results);

	if (!out) {
		std::cout << "file " << Results << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			out << a.Scheme[i];

		}
		else {
			out << "," << a.Scheme[i];
		}
	}
	out.close();
	////////////Schemes////////////////////////////////////////////////

		out.open(S1);

	if (!out) {
		std::cout << "file " << S1 << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			if (a.Scheme[i] == 1) {
				out << 1;
			}
			else {
				out << ",";
			}


		}
		else {
			if (a.Scheme[i] == 1) {
				out << "," << 1;
			}
			else {
				out << ",";
			}
		}
	}
	out.close();
	/////////////////////Scheme 2//////////////////////////////

	out.open(S2);

	if (!out) {
		std::cout << "file " << S2 << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (currentGame == 0) {
			if (a.Scheme[i] == 2) {
				out << 1;
			}
			else {
				out << "," ;
			}


		}
		else {
			if (a.Scheme[i] == 2) {
				out << "," << 1;
			}
			else {
				out << ",";
			}
		}
	}
	out.close();
	//////////////Scheme 3////////////////////////////////////////

	out.open(S3);

	if (!out) {
		std::cout << "file " << S3 << " could not be opened " << std::endl;
		exit(1);	//Could not open file, therefore, Exit
	}
	for (int i = 0; i < gameLength; i++) {
		if (i == 0) {
			if (a.Scheme[i] == 3) {
				out << 1;
			}
			else {
				out << ",";
			}


		}
		else {
			if (a.Scheme[i] == 3) {
				out << "," << 1;
			}
			else {
				out << ",";
			}
		}
	}
	out.close();
	
}

int RpsGameManager::getCurrentGame() { //Returns the current round
	return currentGame;
}

void RpsGameManager::updateScore(STATES GameStatus) { // Adds 1 to userScore if AI wins, Substracts 1 to userScore if AI loses
	if (GameStatus == STATES::Loss) {
		userScore--;
	}
	else if (GameStatus == STATES::Win) {
		userScore++;
	}
}