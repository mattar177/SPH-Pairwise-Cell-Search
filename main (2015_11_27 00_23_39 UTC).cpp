#include "data.h"
#include "functions.h"
#include <iostream>
#include <time.h>


int main()
{
	int selection;

	MakeGrid grid(NumCells);
	Results pRes(NumPoints);
	ParticleList pArray(NumPoints);

	double time;
	clock_t start = clock();

	GeneratePoints(pArray);
	PointsInCells(pArray, grid);

	//for (int c = 0; c < grid[0][0].counter; c++)
	//{
	//	std::cout << grid[0][0].pointid[c] << "\n";
	//}

	for (int a = 0; a < NumCells; a++)
	{
		FindNeighbours(a, pArray, grid, pRes);
	}

	std::cout << pRes[2000].results.size() << "\n";

	time = (double)(clock() - start) / CLOCKS_PER_SEC;
	std::cout << "\n" << time << " seconds\n\nPress 1 to write results to text file or 0 to close: ";
	std::cin >> selection;
	if (selection == 1)
	{
		OutputResults(pRes);
	}

	return 0;
}