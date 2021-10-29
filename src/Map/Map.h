#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "Case/Case.h"
#include "../Common/Point.h"
#include "../Wind/Wind.h"
#include "../Boat.h"

class Map{
private:
    std::vector<std::vector<Case*>> _cases;
    std::vector<Wind*> _winds;
    Boat* _boat;

    static const int PROBA_MOVE;

    std::vector<std::pair<LocalWind*, Point>> associateWindsToPosition(Wind*);
    Point offsetDirection(Wind*);
    void setWind(std::vector<std::pair<LocalWind*, Point>>);

public:
    Map();
    Map(size_t size);
    ~Map();

    Case* caseAt(const Point&) const;
    void setCase(Point, Case*);

    Point goToOtherSide(Point);

    void boat(Boat*);
    Boat* boat() const;

    std::vector<Wind*> wind();

    bool outOfBounds(const Point) const;

    void addWind(Wind*);

    unsigned int getSize();

    void tick();
    void moveWind(Wind*);
    void rotateWind(Wind*, int);
};

#endif