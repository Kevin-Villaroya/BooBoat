#ifndef __CASE_ISLAND_H__
#define __CASE_ISLAND_H__

#include "Case.h"

class CaseIsland : virtual public Case{
private:
    bool market;

public:
    CaseIsland(Point);

    LocalWind& wind() const;

    bool isTraversable() const override;

    bool hasMarket() const override;
    void putMarket();

    bool isHarbor(CaseIsland*) const override;
    bool isHarbor() const override;
};

#endif