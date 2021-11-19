#ifndef BOAT_POINT_H
#define BOAT_POINT_H

#include <functional>


struct Point
{
	int x;
	int y;

	bool operator==(const Point&) const = default;
};

template<>
struct std::hash<Point>
{
	size_t operator()(const Point& p) const
	{
		return std::hash<int>{}(1000*p.x+p.y);
	}
};

#endif
