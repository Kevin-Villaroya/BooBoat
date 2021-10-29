#include "Map.h"
#include "Case/CaseWater.h"
#include "Case/CaseIsland.h"

#include <iostream>

const int Map::PROBA_MOVE = 2;

Map::Map() : Map(20){}

Map::Map(size_t size){
    for(unsigned int i = 0; i < size; i++){
        std::vector<Case*> c;
        for(unsigned int j = 0; j < size; j++){
            CaseWater* newCase = new CaseWater(Point(i, j));
            c.push_back(newCase);
        }
        this->_cases.push_back(c);
    }
}

Map::~Map(){
    for(unsigned int i = 0; i < this->_winds.size(); i++){
        delete this->_winds[i];
    }

    for(unsigned int i = 0; i < this->_cases.size(); i++){
        for(unsigned int j = 0; j < this->_cases.size(); j++){
            delete this->_cases[i][j];
        }
    }
}

Case* Map::caseAt(const Point& point) const{
    if( !this->outOfBounds(point) ){
        return this->_cases[point.x][point.y];
    }

    return nullptr;
}

void Map::setCase(const Point point, Case* c){
    if( !this->outOfBounds(point) ){
        Case* oldCase = this->_cases[point.x][point.y];
        this->_cases[point.x][point.y] = c;
        delete oldCase;
    }
}

Point Map::goToOtherSide(Point p){
    int x = (p.x + this->getSize()) % this->getSize();
    int y = (p.y + this->getSize()) % this->getSize();


    Point newpoint{x, y};

    return newpoint;
}

void Map::boat(Boat* boat){
    this->_boat = boat;
}

Boat* Map::boat() const{
    return this->_boat;
}

std::vector<Wind*> Map::wind(){
    return this->_winds;
}

bool Map::outOfBounds(Point p) const{
    return p.x < 0 || p.y < 0 || (unsigned int)p.x >= this->_cases.size() || (unsigned int)p.y >= this->_cases.size();
}

void Map::addWind(Wind* w){
    this->_winds.push_back(w);
}

unsigned int Map::getSize(){
    return ((unsigned int)this->_cases.size());
}

void Map::tick(){
    for(unsigned int i = 0; i < this->_winds.size(); i++){
        this->_winds[i]->tick();
        this->moveWind(this->_winds[i]);
    }
}

void Map::moveWind(Wind* w){
    int random = rand() % 100;

    std::vector<std::pair<LocalWind*, Point>> temp;

    if(random <= Map::PROBA_MOVE){
        temp = this->associateWindsToPosition(w);

        Point offset = this->offsetDirection(w);

        for(unsigned int i = 0; i < temp.size(); i++){
            temp[i].second.x += offset.x;
            temp[i].second.y += offset.y;
        }

        this->setWind(temp);
    }
}

std::vector<std::pair<LocalWind*, Point>> Map::associateWindsToPosition(Wind* w){
    std::vector<std::pair<LocalWind*, Point>> temp;

    for(unsigned int i = 0; i < this->getSize(); i++){
       for(unsigned int j = 0; j < this->getSize(); j++){
        Case* c = this->_cases[i][j];

            if(c->hasWind() && w->contains(c->wind())){
                std::pair<LocalWind*, Point> paire{c->wind(), Point(i, j)};
                c->removeWind();
                temp.push_back(paire);
            }
        } 
    }

    return temp;
}

Point Map::offsetDirection(Wind* w){
    Point offset;

    switch(w->getGeneralDirection()){
        case Direction::North:
            offset.x = 0;
            offset.y = -1;
            break;
        case Direction::NorthWest:
            offset.x = -1;
            offset.y = -1;
            break;
        case Direction::West:
            offset.x = -1;
            offset.y = 0;
            break; 
        case Direction::SouthWest:
            offset.x = -1;
            offset.y = 1;
            break; 
        case Direction::South:
            offset.x = 0;
            offset.y = 1;
            break; 
        case Direction::SouthEast:
            offset.x = 1;
            offset.y = 1;
            break; 
        case Direction::East:
            offset.x = 1;
            offset.y = 0;
            break; 
        case Direction::NorthEast:
            offset.x = 1;
            offset.y = -1;
            break; 
        default:
            break;
    }

    return offset;
}   

void Map::setWind(std::vector<std::pair<LocalWind*, Point>> temp){
    for(unsigned int i = 0; i < temp.size(); i++){
        if(!this->outOfBounds(temp[i].second)){
            this->caseAt(temp[i].second)->wind(temp[i].first);
        }else{
            this->caseAt(this->goToOtherSide(temp[i].second))->wind(temp[i].first);
        }
    }
}