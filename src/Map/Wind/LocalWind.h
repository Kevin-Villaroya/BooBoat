#ifndef __LOCAL_WIND_H__
#define __LOCAL_WIND_H__

#include "LocalWind.fwd.h"
#include "Wind.fwd.h"
#include "../../Common/Direction.h"
#include <SFML/Graphics.hpp>

class LocalWind : virtual public sf::Sprite{
private:
    Wind* windReference;
    Direction _direction;

    void rotateSprite();
public:
    LocalWind(Wind*);
    LocalWind(Wind*, Direction);

    void direction(Direction);
    Direction direction() const;

};

#endif