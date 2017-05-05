#include <iostream>
#include <random>

using namespace std;

class RNG{
public:
	RNG::RNG() : gen(std::random_device()()) {} 
	
	// Seeds the mt19937.

	/*float getRandom(float x, float y) {
	float min, max;
	if (x > y)
	{
	max = x;
	min = y;
	}
	else
	{
	max = y;
	min = x;
	}
	std::uniform_real_distribution<float> dis(min, std::nextafter(max, DBL_MAX));
	float random = dis(gen);
	return random;
	}*/

	int getRandom(int x, int y)
	{
		int min, max;
		if (x > y)
		{
			max = x;
			min = y;
		}
		else
		{
			max = y;
			min = x;
		}
		std::uniform_int_distribution<int> dis(min, max);
		int random = dis(gen);
		return random;
	}

private:
	std::mt19937 gen;
};