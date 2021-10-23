#include "CaseWater.h"
#include "../../Texture/TextureLoader.h"

CaseWater::CaseWater(Point p) : Case(p){
    this->setTexture(*TextureLoader::getWaterTexture());
}

bool CaseWater::isThrowable() const{
    return true;
}

bool CaseWater::hasMarket() const{
    return false;
}