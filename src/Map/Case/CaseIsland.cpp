#include "CaseIsland.h"
#include "../../Texture/TextureLoader.h"

CaseIsland::CaseIsland(Point p) : Case(p){
    this->market = false;
    this->setTexture(*TextureLoader::getLandTexture());
}

bool CaseIsland::isThrowable() const{
    return false;
}

bool CaseIsland::hasMarket() const{
    return market;
}

void CaseIsland::putMarket(){
    this->market = true;
}