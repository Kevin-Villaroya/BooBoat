#include "Boat.h"
#include "Texture/TextureLoader.h"
#include "Map/Map.h"

Boat::Boat(Point point, Map& map) : _pos(point), _map(&map){
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
