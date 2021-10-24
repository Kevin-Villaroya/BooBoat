#include "Case.h"

Case::Case(Point point) {
    this->setPosition(sf::Vector2f(point.x * 33, point.y * 33));
}

Case::~Case() {}

LocalWind& Case::wind() const{
    return *this->_localWind;
}