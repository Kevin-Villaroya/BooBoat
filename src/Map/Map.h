#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "Case/Case.h"
#include "../Common/Point.h"

class Map{
private:
    std::vector<std::vector<Case*>> _cases;

public:
    Map();
    Map(size_t size);

    Case* caseAt(const Point&) const;
    void setCase(Point, Case*);

    bool outOfBounds(Point);

    unsigned int getSize();
};

#endif