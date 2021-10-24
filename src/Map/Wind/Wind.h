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
    Direction getAPossibleDirection();

    void tick();
};

#endif
