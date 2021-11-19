#include "Boat.h"
#include "Texture/TextureLoader.h"
#include "Map/Map.h"

Boat::Boat(Point point, Map& map) : _pos(point), _map(&map), _tick(0) {
  this->setPosition(sf::Vector2f(point.x * 33, point.y * 33));
  this->setTexture(*TextureLoader::getBoatTexture());
}

Knowledge Boat::perception() const
{
    constexpr int ViewRange = 2;

    Knowledge k;
    k.pos(_pos);
    for(int x_offset = -ViewRange; x_offset < ViewRange; ++x_offset)
    {
        for(int y_offset = -ViewRange; y_offset < ViewRange; ++y_offset)
        {
            Point other{_pos.x + x_offset, _pos.y + y_offset};
            if(Case* other_case = _map->caseAt(other))
            {
                if(LocalWind* local_wind = other_case->wind())
                {
                    k.addWind(other, local_wind->direction());
                }
                else
                {
                    k.addWind(other, Direction::None);
                }
            }
        }
    }
	return k;
}

void Boat::tick()
{
	_ai.addPerception(perception());

    if(this->_tick == 0)
    {
        move(_ai.nextDirection());
    }
	else
    {
        this->_tick--;
    }
}

void Boat::move(Direction dir)
{
    Case* c = _map->caseAt(this->_pos + dir);

    if(c != nullptr)
    {
        if(LocalWind* local_wind = c->wind())
        {
            this->_tick = moveTurnsInWind(dir, local_wind->direction());
        }
        else
        {
            this->_tick = moveTurnsInWind(dir, Direction::None);
        }
    }

    this->_pos += dir;
    this->setPosition(sf::Vector2f(this->_pos.x * 33, this->_pos.y * 33));
}

Point Boat::pos() const
{
	return _pos;
}
