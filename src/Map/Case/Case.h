#ifndef __CASE_H__
#define __CASE_H__

#include <SFML/Graphics.hpp>
#include "../Wind/LocalWind.h"
#include "../../Common/Point.h"

class CaseIsland;

class Case : virtual public sf::Sprite{
private:
    LocalWind* _localWind;

public:
    Case(Point);

    virtual ~Case();

    bool hasWind();

    LocalWind* wind() const;
    void wind(LocalWind*);

    void removeWind();

    virtual bool isThrowable() const = 0;
    virtual bool hasMarket() const = 0;

    virtual bool isHarbor(CaseIsland*) const = 0;
    virtual bool isHarbor() const = 0;
};

#endif