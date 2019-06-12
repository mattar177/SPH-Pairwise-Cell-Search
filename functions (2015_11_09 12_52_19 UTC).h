#pragma once

#include "data.h"

void GeneratePoints(ParticleList(& pArray));

void PointsInCells(ParticleList(& pArray), MakeGrid(& grid));

void FindNeighbours(int a, ParticleList(& pArray), MakeGrid(& grid), Results(& pRes));

double GenerateRandom();

void OutputResults(Results(& pRes));