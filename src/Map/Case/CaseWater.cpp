#include "CaseWater.h"
#include "../../Texture/TextureLoader.h"

CaseWater::CaseWater(Point p) : Case(p){
    this->setTexture(*TextureLoader::getWaterTexture());
}

bool CaseWater::isTraversable() const{
    return true;
}

bool CaseWater::hasMarket() const{
    return false;
}

bool CaseWater::isHarbor(CaseIsland* m) const{
    for(unsigned int i = 0; i < adjacentMarkets.size(); i++){
        if(this->adjacentMarkets[i] == m){
            return true;
        }
    }

    return false;
}

bool CaseWater::isHarbor() const{
    return !this->adjacentMarkets.empty();
}

void CaseWater::addAdjacentMarket(CaseIsland* c){
    this->adjacentMarkets.push_back(c);

    this->setTexture(*TextureLoader::getAnchorTexture());
}