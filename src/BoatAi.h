#ifndef BOAT_BOATAI_H
#define BOAT_BOATAI_H

#include "Knowledge.h"
#include "Common/Direction.h"
#include <vector>


class BoatAi
{
	Knowledge _knowledge;
	std::vector<Direction> _plan;
	Point _destination{0,0};

	void computePlan();
	std::vector<Direction> availableDirections(Point pos) const;
	float moveCost(Point from, Direction dir) const;

public:
	void addPerception(Knowledge perception);
	Direction nextDirection();
};

#endif
