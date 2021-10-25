#include <iostream>
#include "Map/Generation/MapGenerator.h"
#include "Map/Map.h"
#include "Engine/Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    size_t sizeMap = 20;
    size_t nbIslands = 4;
    size_t nbMarkets = 6;
    size_t nbWinds = 5;

    MapGenerator* generator = MapGenerator::getInstance();

    generator->generateMap(sizeMap, nbIslands);
    generator->addMarketPlaces(nbMarkets);
    generator->addWinds(nbWinds);
    generator->addBoat();

    Map* map = generator->getGeneratedMap();

    Engine engine(map);
    engine.run();

    generator->deleteInstance();

    return EXIT_SUCCESS;
}

