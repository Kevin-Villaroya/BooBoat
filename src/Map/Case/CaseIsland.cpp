#include "CaseIsland.h"
#include "../../Texture/TextureLoader.h"

CaseIsland::CaseIsland(Point p) : Case(p){
    this->market = false;
    this->setTexture(*TextureLoader::getLandTexture());
}

bool CaseIsland::isTraversable() const{
    return false;
}

bool CaseIsland::hasMarket() const{
    return market;
}

void CaseIsland::putMarket(){
    this->market = true;
    this->setTexture(*TextureLoader::getMarketTexture());
}

bool CaseIsland::isHarbor(CaseIsland* m) const{
    return false;
}

bool CaseIsland::isHarbor() const{
    return false;
}