#ifndef BOAT_BOAT_H
#define BOAT_BOAT_H

#include "Common/Point.h"
#include <SFML/Graphics.hpp>

class Boat : virtual public sf::Sprite
{
private:
	Point _pos;
public:
	Boat(Point);
	void tick();
	
	Point pos() const;
};

#endif
