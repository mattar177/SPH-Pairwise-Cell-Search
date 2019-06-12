#pragma once

#include <vector>

#define NumPoints 1000000
#define NumPointsxory std::sqrt(NumPoints)
#define NumCellsxory (NumPointsxory / 2)
#define NumCells ((NumCellsxory) * (NumCellsxory))
#define Spacing (1 / NumPointsxory)
#define SearchRadsq ((2 * Spacing) * (2 * Spacing))

struct Particle
{
	size_t id;
	double x;
	double y;
};

typedef std::vector<Particle> ParticleList;

struct cell{

	std::vector<int> pointid;
	cell(){ pointid.reserve(4); }

};

typedef std::vector<cell> MakeGrid;

struct point{

	std::vector<int> results;
	point(){ results.reserve(13); }

};

typedef std::vector<point> Results;