#ifndef __CASE_WATER_H__
#define __CASE_WATER_H__

#include "Case.h"
#include <vector>

class CaseWater : virtual public Case{
private:
    std::vector<CaseIsland*> adjacentMarkets;

public:
    CaseWater(Point p);

    bool isThrowable() const override;
    bool hasMarket() const override;

    bool isHarbor(CaseIsland*) const override;
    bool isHarbor() const override;

    void addAdjacentMarket(CaseIsland*);
};

#endif