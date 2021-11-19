#ifndef BOAT_DIRECTION_H
#define BOAT_DIRECTION_H

#include <string>
#include <iostream>
#include "Point.h"

enum Direction
{
	North = 6,//-Y
	NorthEast = 5,
	East = 4,//+X
	SouthEast = 3,
	South = 2,//+Y
	SouthWest = 1,
	West = 0,//-X
	NorthWest = 7,
	None = 8
};

inline std::ostream &operator << ( std::ostream& strm, Direction dir )
{
   const std::string nameTT[] = { "North", "NorthEast", "East", "SouthEast", "South", "SouthWest", "West", "NorthWest", "None" };
   return strm << nameTT[dir];
}

inline Direction rotate(Direction dir, int value){
	return static_cast<Direction>((dir+value + 8) % 8);
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
