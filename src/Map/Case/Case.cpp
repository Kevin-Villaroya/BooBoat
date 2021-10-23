#include "Case.h"

Case::Case(Point point) {
    this->setPosition(sf::Vector2f(point.x * 35, point.y * 35));
}

Case::~Case() {}

LocalWind& Case::wind() const{
    return *this->_localWind;
}