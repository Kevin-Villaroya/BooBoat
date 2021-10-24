#include "Map.h"
#include "Case/CaseWater.h"
#include "Case/CaseIsland.h"

#include <iostream>

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

bool Map::outOfBounds(Point p) const{
    return p.x < 0 || p.y < 0 || (unsigned int)p.x >= this->_cases.size() || (unsigned int)p.y >= this->_cases.size();
}

unsigned int Map::getSize(){
    return ((unsigned int)this->_cases.size());
}