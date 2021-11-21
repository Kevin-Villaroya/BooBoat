#ifndef BOAT_KNOWLEDGE_H
#define BOAT_KNOWLEDGE_H

#include <unordered_map>
#include <unordered_set>
#include <optional>
#include "Common/Point.h"
#include "Common/Direction.h"

struct Knowledge
{
private:
	std::optional<Point> _pos;
	std::unordered_map<Point, Direction> _winds;
	std::unordered_set<Point> _land;

    void mergePos(const Knowledge& other)
    {
        if(other._pos) _pos = other._pos;
    }

    void mergeWinds(const Knowledge& other)
    {
        //Merge with priority on the new values
		auto copy = std::move(_winds);
		_winds = other._winds;
		_winds.merge(copy);
    }

    void mergeLand(const Knowledge& other)
    {
        auto copy = other._land;
        _land.merge(copy);
    }

public:
	std::optional<Point> pos() const { return _pos; }
	void pos(Point pos) { _pos = pos; }
	void addWind(Point pos, Direction w)
	{
		_winds[pos] = w;
	}

    void addLand(Point pos)
    {
        _land.insert(pos);
    }

	Direction windDirectionAt(Point pos) const
	{
		auto it = _winds.find(pos);
		if(it == _winds.end()) return Direction::None;
		return it->second;
	}

    bool landAt(Point pos) const
	{
		return _land.contains(pos);
	}

	void merge(const Knowledge& other)
	{
		mergePos(other);
		mergeWinds(other);
        mergeLand(other);
	}
};

#endif
