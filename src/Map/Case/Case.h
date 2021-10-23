#ifndef __CASE_H__
#define __CASE_H__

#include <SFML/Graphics.hpp>
#include "../Wind/LocalWind.h"
#include "../../Common/Point.h"

class Case : virtual public sf::Sprite{
private:
    LocalWind* _localWind;

public:
    Case(Point);

    virtual ~Case();

    LocalWind& wind() const;

    virtual bool isThrowable() const = 0;
    virtual bool hasMarket() const = 0;
};

#endif