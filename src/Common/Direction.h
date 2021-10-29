#ifndef BOAT_DIRECTION_H
#define BOAT_DIRECTION_H

#include "Point.h"


enum class Direction
{
	North,//-Y
	NorthEast,
	East,//+X
	SouthEast,
	South,//+Y
	SouthWest,
	West,//-X
	NorthWest,
	None
};

inline Point& operator+=(Point& pos, Direction dir)
{
	switch(dir)
	{
	case Direction::North:
	case Direction::NorthWest:
	case Direction::NorthEast:
		--pos.y;
		break;
	case Direction::South:
	case Direction::SouthWest:
	case Direction::SouthEast:
		++pos.y;
		break;
	default:
		break;
	}

	switch(dir)
	{
	case Direction::East:
	case Direction::NorthEast:
	case Direction::SouthEast:
		++pos.x;
		break;
	case Direction::West:
	case Direction::SouthWest:
	case Direction::NorthWest:
		--pos.x;
		break;
	default:
		break;
	}

	return pos;
}

inline Point operator+(Point pos, Direction dir)
{
	pos += dir;
	return pos;
}

inline Point operator+(Direction dir, Point pos)
{
	return pos + dir;
}

#endif
