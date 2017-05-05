#include "History.h"

History::History() {} // Default Constructor

History::History(std::vector<PLAY> UserHistory, std::vector<PLAY> OpponentHistory, std::vector<STATES> WinLossHistory, std::vector<int> Scheme, std::vector<int> Score) {
	//Non-default constructor that initialises the data-members of the object with the
	// given arguments
	this->UserHistory = UserHistory;
	this->OpponentHistory = OpponentHistory;
	this->WinLossHistory = WinLossHistory;
	this->Scheme = Scheme;
	this->Score = Score;
}