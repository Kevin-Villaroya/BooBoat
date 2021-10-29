#include "Wind.h"

const int Wind::PROBA_ROTATE = 5;


Wind::Wind(Direction d) : generalDirection(d){}

Wind::~Wind(){
    for(unsigned int i = 0; i < this->_winds.size(); i++){
        delete this->_winds[i];
    }
}

void Wind::addLocalWind(LocalWind* localWind){
    this->_winds.push_back(localWind);
}

bool Wind::contains(LocalWind* lc){
    for(unsigned int i = 0; i < this->_winds.size(); i++){
        if(lc == this->_winds[i]){
            return true;
        }
    }
    return false;
}

Direction Wind::getGeneralDirection(){
    return this->generalDirection;
}

Direction Wind::getAPossibleDirectionForALocalWind(){
    unsigned int random = rand() % 4;

    bool sameDirection = random == 0 || random == 1;
    bool leftDirection = random == 2;
    bool rightDirection = random == 3;

    switch (this->generalDirection){
    case Direction::East:
        if(sameDirection){
            return Direction::East;
        }else if(leftDirection){
            return Direction::NorthEast;
        }else if(rightDirection){
            return Direction::SouthEast;
        }
        break;
    case Direction::SouthEast:
        if(sameDirection){
            return Direction::SouthEast;
        }else if(leftDirection){
            return Direction::East;
        }else if(rightDirection){
            return Direction::South;
        }
        break;
    case Direction::South:
        if(sameDirection){
            return Direction::South;
        }else if(leftDirection){
            return Direction::SouthEast;
        }else if(rightDirection){
            return Direction::SouthWest;
        }
        break;
    case Direction::SouthWest:
        if(sameDirection){
            return Direction::SouthWest;
        }else if(leftDirection){
            return Direction::West;
        }else if(rightDirection){
            return Direction::South;
        }
        break;
    case Direction::West:
        if(sameDirection){
            return Direction::West;
        }else if(leftDirection){
            return Direction::SouthWest;
        }else if(rightDirection){
            return Direction::NorthWest;
        }
        break;
    case Direction::NorthWest:
        if(sameDirection){
            return Direction::NorthWest;
        }else if(leftDirection){
            return Direction::West;
        }else if(rightDirection){
            return Direction::North;
        }
        break;
    case Direction::North:
        if(sameDirection){
            return Direction::North;
        }else if(leftDirection){
            return Direction::NorthEast;
        }else if(rightDirection){
            return Direction::NorthWest;
        }
        break;
    case Direction::NorthEast:
        if(sameDirection){
            return Direction::NorthEast;
        }else if(leftDirection){
            return Direction::North;
        }else if(rightDirection){
            return Direction::East;
        }
        break;
    default:
        return Direction::None;
        break;
    }
    return Direction::None;
}

void Wind::changeDirection(){
    int random = (rand() % 2) - 1;

    this->generalDirection = rotate(this->generalDirection, random);

    for(unsigned int i = 0; i < this->_winds.size(); i++){
        this->_winds[i]->direction( rotate(this->_winds[i]->direction(), random) );
    }
}

void Wind::tick(){
    int random_rotate = rand() % 100;

    if(random_rotate <= Wind::PROBA_ROTATE){
        this->changeDirection();
    }
}