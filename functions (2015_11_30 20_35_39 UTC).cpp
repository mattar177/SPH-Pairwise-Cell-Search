#include "functions.h"
#include "data.h"
#include <fstream>

void GeneratePoints(ParticleList(& pArray))
{
	int j2 = 0;

	for (int i = 0; i < NumPoints; i++)
	{
		pArray[i].id = i;
	}

	for (double j = 0; j < NumPointsxory; j++)
	{
		for (double k = 0; k < NumPointsxory; k++)
		{
			pArray[j2].x = (k / NumPointsxory) + (Spacing / 2);
			pArray[j2].y = (j / NumPointsxory) + (Spacing / 2);
			j2++;
		}
	}
	
	//for (int j = 0; j < NumPoints; j++)
	//{
	//	pArray.x[j] = GenerateRandom();
	//	pArray.y[j] = GenerateRandom();
	//}
}


void PointsInCells(ParticleList(& pArray), MakeGrid(& grid))
{
	int cellx, celly, cell;

	for (int count = 0; count < NumPoints; count++)
	{
		//if (pArray.x[count] == 1 && pArray.y[count] == 1)
		//{
		//	cellx = 9;
		//	celly = 9;
		//}
		//else if (pArray.x[count] == 1)
		//{
		//	cellx = 9;
		//	celly = floor(pArray.y[count] * 10);
		//}
		//else if (pArray.y[count] == 1)
		//{
		//	cellx = floor(pArray.x[count] * 10);
		//	celly = 9;
		//}
		//else
		//{
		//	cellx = floor(pArray.x[count] * 10);
		//	celly = floor(pArray.y[count] * 10);
		//}

		//cellx = floor((pArray.x[count] - (1/10000000)) * 10);
		//celly = floor((pArray.y[count] - (1/10000000)) * 10);
		//grid[cellx][celly].pointid[grid[cellx][celly].counter] = pArray.id[count];
		cellx = floor(pArray[count].x * NumCellsxory);
		celly = floor(pArray[count].y * NumCellsxory);
		cell = cellx + (celly * NumCellsxory);
		grid[cell].pointid.push_back(pArray[count].id);
	}
}


void FindNeighbours(int a, ParticleList(& pArray), MakeGrid(& grid), Results(& pRes))
{
	double distance;
	int a2;
	//clock_t start = clock();

	for (int b = 0; b < grid[a].pointid.size(); b++)
	{
		for (int c = 0; c < grid[a].pointid.size(); c++)
		{
			distance = pow((pArray[grid[a].pointid[b]].x - pArray[grid[a].pointid[c]].x), 2) + pow((pArray[grid[a].pointid[b]].y - pArray[grid[a].pointid[c]].y), 2);

			if (distance <= SearchRadsq)
			{
				pRes[grid[a].pointid[b]].results.push_back(grid[a].pointid[c]);
			}
		}

		
		a2 = a + NumCellsxory - 1;

		if ((a2 + 1) % (int)NumCellsxory != 0 && a2 < NumCells)
		{
			for (int d = 0; d < grid[a2].pointid.size(); d++)
			{
				distance = pow((pArray[grid[a].pointid[b]].x - pArray[grid[a2].pointid[d]].x), 2) + pow((pArray[grid[a].pointid[b]].y - pArray[grid[a2].pointid[d]].y), 2);
				
				if (distance <= SearchRadsq)
				{
					pRes[grid[a].pointid[b]].results.push_back(grid[a2].pointid[d]);
					pRes[grid[a2].pointid[d]].results.push_back(grid[a].pointid[b]);
				}
			}
		}
		

		a2 = a + NumCellsxory;

		if (a2 < NumCells)
		{
			for (int e = 0; e < grid[a2].pointid.size(); e++)
			{
				distance = pow((pArray[grid[a].pointid[b]].x - pArray[grid[a2].pointid[e]].x), 2) + pow((pArray[grid[a].pointid[b]].y - pArray[grid[a2].pointid[e]].y), 2);

				if (distance <= SearchRadsq)
				{
					pRes[grid[a].pointid[b]].results.push_back(grid[a2].pointid[e]);
					pRes[grid[a2].pointid[e]].results.push_back(grid[a].pointid[b]);
				}
			}
		}

		for (a2 = a + 1; a2 <= a + 1 + NumCellsxory; a2 = a2 + NumCellsxory)
		{
			if (a2 % (int)NumCellsxory != 0 && a2 < NumCells)
			{
				for (int f = 0; f < grid[a2].pointid.size(); f++)
				{
					distance = pow((pArray[grid[a].pointid[b]].x - pArray[grid[a2].pointid[f]].x), 2) + pow((pArray[grid[a].pointid[b]].y - pArray[grid[a2].pointid[f]].y), 2);

					if (distance <= SearchRadsq)
					{
						pRes[grid[a].pointid[b]].results.push_back(grid[a2].pointid[f]);
						pRes[grid[a2].pointid[f]].results.push_back(grid[a].pointid[b]);
					}
				}
			}
		}



		//a2 = a + 1;

		//if (a2 % (int)NumCellsxory != 0 && a2 < NumCells)
		//{
		//	for (int f = 0; f < grid[a2].pointid.size(); f++)
		//	{
		//		distance = pow((pArray[grid[a].pointid[d]].x - pArray[grid[a2].pointid[f]].x), 2) + pow((pArray[grid[a].pointid[d]].y - pArray[grid[a2].pointid[f]].y), 2);

		//		if (distance <= SearchRadsq)
		//		{
		//			pRes[grid[a].pointid[d]].results.push_back(grid[a2].pointid[f]);
		//			pRes[grid[a2].pointid[f]].results.push_back(grid[a].pointid[d]);
		//		}
		//	}
		//}
	}
}


double GenerateRandom()
{
	return rand() / (RAND_MAX + 1.0);
}


void OutputResults(Results(& pRes))
{
	std::ofstream file;
	file.open("results.txt");

	for (int i = 0; i < NumPoints; i++)
	{
		file << "\nPoint id = " << i << " neighbours: ";

		for (int j = 0; j < pRes[i].results.size(); j++)
		{
			file << pRes[i].results[j] << ", ";
		}
	}
}