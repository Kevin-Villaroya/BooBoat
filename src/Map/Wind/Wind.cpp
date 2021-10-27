#include "Wind.h"

Wind::Wind(Direction d) : generalDirection(d){}

Wind::~Wind(){
    for(unsigned int i = 0; i < this->_winds.size(); i++){
        delete this->_winds[i];
    }
}

void Wind::addLocalWind(LocalWind* localWind){
    this->_winds.push_back(localWind);
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

void Wind::tick(){
    //TODO
}