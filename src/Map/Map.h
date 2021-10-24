#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "Case/Case.h"
#include "../Common/Point.h"
#include "../Wind/Wind.h"

class Map{
private:
    std::vector<std::vector<Case*>> _cases;
    std::vector<Wind*> _winds;

public:
    Map();
    Map(size_t size);
    ~Map();

    Case* caseAt(const Point&) const;
    void setCase(Point, Case*);

    bool outOfBounds(const Point) const;

    void addWind(Wind*);

    unsigned int getSize();
};

#endif