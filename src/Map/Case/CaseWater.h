#ifndef __CASE_WATER_H__
#define __CASE_WATER_H__

#include "Case.h"

class CaseWater : virtual public Case{
public:
    CaseWater(Point p);

    bool isThrowable() const override;
    bool hasMarket() const override;
};

#endif