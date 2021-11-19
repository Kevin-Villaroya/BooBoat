#ifndef BOAT_BOAT_H
#define BOAT_BOAT_H

#include "Common/Point.h"
#include <SFML/Graphics.hpp>
#include "Knowledge.h"
#include "BoatAi.h"

class Boat : virtual public sf::Sprite
{
private:
	Point _pos;
	BoatAi _ai;
    class Map* _map;
	int _tick;

	Knowledge perception() const;

public:
	Boat(Point, Map&);
	void tick();
	void move(Direction dir);

	Point pos() const;
};

#endif
