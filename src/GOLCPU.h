#pragma once
#include "GOL.h"
class GOLCpu : public GOL
{
public:
	GOLCpu(){}
private:
	int getAliveNeighbours(int i, int j, bool* arr);
	virtual void calculateGol() override;
};