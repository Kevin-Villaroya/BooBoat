#ifndef BOAT_KNOWLEDGE_H
#define BOAT_KNOWLEDGE_H

#include <unordered_map>
#include "Common/Point.h"
#include "Wind.h"

struct Knowledge
{
private:
	Point _pos;
	std::unordered_map<Point, Wind> _winds;

public:
	Knowledge(Point pos)
		:_pos(pos)
	{}

	Point pos() const { return _pos; }
	void pos(Point pos) { _pos = pos; }
	void addWind(Point pos, Wind w)
	{
		_winds[pos] = w;
	}

	void merge(const Knowledge& other)
	{
		_pos = other._pos;
		//TODO
	}
};

#endif
