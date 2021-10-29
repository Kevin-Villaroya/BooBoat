#include "Boat.h"

Knowledge Boat::perception() const
{
	return Knowledge{_pos};
}

void Boat::tick()
{
	_ai.addPerception(perception());
	move(_ai.nextDirection());
}

void Boat::move(Direction dir)
{
	//TODO
}

Point Boat::pos() const
{
	return _pos;
}
