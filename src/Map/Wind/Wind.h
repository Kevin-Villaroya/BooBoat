#ifndef __WIND_H__
#define __WIND_H__

#include <vector>

#include "Wind.fwd.h"
#include "LocalWind.fwd.h"
#include "../Case/Case.h"

class Wind {
private:
    std::vector<LocalWind*> _winds;
    Direction generalDirection;

public:
    Wind(Direction);
    ~Wind();

    void addLocalWind(LocalWind*);

    /**
    * make a possible wind direction for is locals wind
    * 50% same direction, 25% for each side direction
    **/ 
    Direction getAPossibleDirectionForALocalWind();
    void changeDirection();

    void tick();
};

#endif
