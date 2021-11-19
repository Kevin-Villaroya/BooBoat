#include "Boat.h"
#include "Texture/TextureLoader.h"

Boat::Boat(Point point) : _pos(point){
  this->setPosition(sf::Vector2f(point.x * 33, point.y * 33));
  this->setTexture(*TextureLoader::getBoatTexture());
}

Knowledge Boat::perception() const
{
    Knowledge k;
    k.pos(_pos);
	return k;
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
