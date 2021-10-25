#include "Boat.h"
#include "Texture/TextureLoader.h"

Boat::Boat(Point point) : _pos(point){
  this->setPosition(sf::Vector2f(point.x * 33, point.y * 33));
  this->setTexture(*TextureLoader::getBoatTexture());
}

Point Boat::pos() const{
  return this->_pos;
}