#include "LocalWind.h"
#include "../../Texture/TextureLoader.h"
#include "Wind.h"
#include <iostream>

LocalWind::LocalWind(Wind* w){
    this->windReference = w;
    this->_direction = w->getAPossibleDirectionForALocalWind();

    this->setTexture(*TextureLoader::getWindTexture());
    this->setOrigin(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2);
    this->rotateSprite();
}

void LocalWind::direction(Direction d ){
    this->_direction = d;
    this->rotateSprite();
}

Direction LocalWind::direction() const{
    return this->_direction;
}

void LocalWind::rotateSprite(){
    switch (this->_direction){
        case Direction::East:
            this->setRotation(0);
            break;
        case Direction::SouthEast:
            this->setRotation(45);
            break;
        case Direction::South:
            this->setRotation(90);
            break;
        case Direction::SouthWest:
            this->setRotation(135);
            break;
        case Direction::West:
            this->setRotation(180);
            break;
        case Direction::NorthWest:
            this->setRotation(225);
            break;
        case Direction::North:
            this->setRotation(270);
            break;
        case Direction::NorthEast:
            this->setRotation(315);
            break;
        default:
            break;
    }
}