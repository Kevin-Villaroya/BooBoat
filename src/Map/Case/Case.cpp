#include "Case.h"
#include <iostream>

Case::Case(Point point) {
    this->_localWind = nullptr;
    this->setPosition(sf::Vector2f(point.x * 33, point.y * 33));
}

Case::~Case() {}

bool Case::hasWind(){
    return this->_localWind != nullptr;
}

LocalWind* Case::wind() const{
    return this->_localWind;
}

void Case::wind(LocalWind* w){
    this->_localWind = w;
    sf::Vector2u size = this->_localWind->getTexture()->getSize();
    this->_localWind->setPosition(this->getPosition().x + size.x / 2, this->getPosition().y + size.y / 2);
}

 void Case::removeWind(){
    this->_localWind = nullptr;
 }