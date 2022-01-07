#include "GOLCPU.h"

int GOLCpu::getAliveNeighbours(int i, int j, bool* arr)
{
	int ans = 0;
	int cx, cy;
	for (int x = i - 1; x <= i + 1; x++)
	{
		for (int y = j - 1; y <= j + 1; y++)
		{
			cx = x;
			cy = y;
			if (x == i && y == j)
			{
				continue;
			}
			if (x < 0 || x >= W || y < 0 || y >= H)
			{
				if (x < 0)
					cx = W - 1;
				else if (x >= W)
					cx = 0;
				if (y < 0)
					cy = H - 1;
				else if (y >= H)
					cy = 0;
				//continue;
			}
			ans += arr[cx + W * cy];
		}
	}
	return ans;
}

void GOLCpu::calculateGol()
{
	for (int i = 0; i < W; i++)
	{
		for (int j = 0; j < H; j++)
		{
			int n = getAliveNeighbours(i, j, oldVal);
			if (oldVal[i + W * j])
			{
				if (n < 2 || n > 3)
					newVal[i + W * j] = false;
				else
					newVal[i + W * j] = true;
			}
			else
			{
				if (n == 3)
					newVal[i + W * j] = true;
			}
		}
	}
}
