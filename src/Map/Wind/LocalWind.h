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

    static LocalWind* LOCALWIND_NULL;
};

inline int getDirectionDelta(Direction direction1, Direction direction2) {
    int diff = abs(direction2 - direction1);
    return (diff < 4) ? diff : 8 - diff;
}

inline int moveTurnsInWind(Direction boat_direction, Direction wind_direction) {
    if(boat_direction == Direction::None || wind_direction == Direction::None)
    {
        return 5;
    }
    else
    {
        int delta = getDirectionDelta(boat_direction, wind_direction);
        int turns = 5;

        switch(delta)
        {
            case 0:
            case 1:
                turns = 1;
                break;

            case 2:
                turns = 2;
                break;

            case 3:
            case 4:
                turns = 10;
                break;
        }

        return turns;
    }
}

#endif
