#ifndef BOAT_KNOWLEDGE_H
#define BOAT_KNOWLEDGE_H

#include <unordered_map>
#include <optional>
#include "Common/Point.h"
#include "Common/Direction.h"

struct Knowledge
{
private:
	std::optional<Point> _pos;
	std::unordered_map<Point, Direction> _winds;

public:
	std::optional<Point> pos() const { return _pos; }
	void pos(Point pos) { _pos = pos; }
	void addWind(Point pos, Direction w)
	{
		_winds[pos] = w;
	}

	Direction windDirectionAt(Point pos) const
	{
		auto it = _winds.find(pos);
		if(it == _winds.end()) return Direction::None;
		return it->second;
	}

	void merge(const Knowledge& other)
	{
		_pos = other._pos;

		//Merge with priority on the new values
		auto copy = std::move(_winds);
		_winds = other._winds;
		_winds.merge(copy);
	}
};

#endif
