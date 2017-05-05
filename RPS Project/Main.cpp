#pragma once
#include <iostream>
#include "RpsGameManager.h"

int main() {
	cout << "Begin";

	RpsGameManager game(1000, 50, 0.05);

	game.run();

	cout << "End";

	system("PAUSE");
	//return 0;
}