#ifndef __LOCAL_WIND_H__
#define __LOCAL_WIND_H__

#include "LocalWind.fwd.h"
#include "Wind.fwd.h"
#include "../../Common/Direction.h"

class LocalWind{
private:
    Wind* windReference;
    Direction _direction;

public:
    LocalWind(Wind*);
    LocalWind(Wind*, Direction);

    void direction(Direction);
    Direction& direction() const;

};

#endif