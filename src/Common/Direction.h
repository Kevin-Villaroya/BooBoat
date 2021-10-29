#ifndef BOAT_DIRECTION_H
#define BOAT_DIRECTION_H

#include <string>
#include <iostream>

enum Direction
{
	North = 6,
	NorthEast = 5,
	East = 4,
	SouthEast = 3,
	South = 2,
	SouthWest = 1,
	West = 0,
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
}

#endif
