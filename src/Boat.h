#ifndef BOAT_BOAT_H
#define BOAT_BOAT_H

#include "Common/Point.h"

class Boat
{
	Point _pos;
public:
	void tick();
	
	Point pos() const;
};

#endif
