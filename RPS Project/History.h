#pragma once
#include "RPS_Tools.h"
#include <iostream>
#include <vector>

using namespace std;

class History {
public:
    std::vector<PLAY> UserHistory;
    std::vector<PLAY> OpponentHistory;
    std::vector<STATES> WinLossHistory;
    std::vector<int> Scheme;
    std::vector<int> Score;
    
    History();
	History(std::vector<PLAY> UserHistory, std::vector<PLAY> OpponentHistory, std::vector<STATES> WinLossHistory, std::vector<int> Scheme, std::vector<int> Score);
	
};
