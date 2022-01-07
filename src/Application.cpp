#include "GOLCPU.h"
#include "GOLGPU.h"
#include <iostream>
int main()
{
	std::cout << "Press G for GPU, Press C for CPU; While running ,Press Space to Pause R to Randomize and A to reset; \n";
	char c;
	std::cin >> c;
	GOL* g = nullptr;
	bool shouldRun = true;
	if (c == 'G')
		g = new GOLGpu();
	else if (c == 'C')
		g = new GOLCpu();
	else
		shouldRun = false;
	if (shouldRun)
		g->run();
}