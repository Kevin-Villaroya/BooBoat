#ifndef BOAT_BOAT_H
#define BOAT_BOAT_H

#include "Common/Point.h"
#include "Knowledge.h"
#include "BoatAi.h"

class Boat
{
	Point _pos;
	BoatAi _ai;

	Knowledge perception() const;

public:
	void tick();
	void move(Direction dir);
	
	Point pos() const;
};

#endif
