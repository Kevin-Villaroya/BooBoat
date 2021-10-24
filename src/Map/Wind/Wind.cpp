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

Direction Wind::getAPossibleDirection(){
    unsigned int random = rand() % 3;

    switch (this->generalDirection){
    case Direction::East:
        if(random == 0){
            return Direction::East;
        }else if(random == 1){
            return Direction::NorthEast;
        }else if(random == 2){
            return Direction::SouthEast;
        }
        break;
    case Direction::SouthEast:
        if(random == 0){
            return Direction::SouthEast;
        }else if(random == 1){
            return Direction::South;
        }else if(random == 2){
            return Direction::East;
        }
        break;
    case Direction::South:
        if(random == 0){
            return Direction::South;
        }else if(random == 1){
            return Direction::SouthEast;
        }else if(random == 2){
            return Direction::SouthWest;
        }
        break;
    case Direction::SouthWest:
        if(random == 0){
            return Direction::SouthWest;
        }else if(random == 1){
            return Direction::West;
        }else if(random == 2){
            return Direction::South;
        }
        break;
    case Direction::West:
        if(random == 0){
            return Direction::SouthWest;
        }else if(random == 1){
            return Direction::West;
        }else if(random == 2){
            return Direction::NorthWest;
        }
        break;
    case Direction::NorthWest:
        if(random == 0){
            return Direction::North;
        }else if(random == 1){
            return Direction::West;
        }else if(random == 2){
            return Direction::NorthWest;
        }
        break;
    case Direction::North:
        if(random == 0){
            return Direction::North;
        }else if(random == 1){
            return Direction::NorthEast;
        }else if(random == 2){
            return Direction::NorthWest;
        }
        break;
    case Direction::NorthEast:
        if(random == 0){
            return Direction::North;
        }else if(random == 1){
            return Direction::NorthEast;
        }else if(random == 2){
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