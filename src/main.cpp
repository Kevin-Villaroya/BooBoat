#include <iostream>
#include "Map/Generation/MapGenerator.h"
#include "Map/Map.h"
#include "Engine/Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    size_t sizeMap = 20;
    size_t nbIslands = 4;
    size_t nbMarkets = 3;

    MapGenerator* generator = MapGenerator::getInstance();

    generator->generateMap(sizeMap, nbIslands);
    /*
    generator.addMarketPlaces(nbMarkets);
    generator.addWind();
    generator.addBoat();
    */

    //generator.generateAll(sizeMap, nbIslands, nbMarkets); same as above

    Map* map = generator->getGeneratedMap();

    Engine engine(map);
    engine.run();

    generator->deleteInstance();

    return EXIT_SUCCESS;
}

