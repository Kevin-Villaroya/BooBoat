#ifndef __MAP_GENERATOR_H
#define __MAP_GENERATOR_H

#include "../Map.h"
#include "../../Common/Point.h"

class MapGenerator{
private:
    static MapGenerator* instance;
    static Map* map;

    static const unsigned int SIZE_MIN_ISLAND;

    Point findNewIslandLocation(unsigned int minSize, unsigned int maxSize);
    void genereateIsland(Point, unsigned int, unsigned int);

    std::vector<std::vector<std::pair<Point, int>>> makeGraph();
    void verifyConnexity();
    void resolveConnexityGraph(std::vector<std::vector<std::pair<Point, int>>>& graph, Point point);
    void setMapConnex(std::vector<std::vector<std::pair<Point, int>>>& graph);
    
    std::vector<Point> getAllCoasts();
    unsigned int addMarketPlacesOnCoast(std::vector<Point>, unsigned int);
    void addMarketPlacesRandomly(unsigned int);

    bool thereIsIslandNear(Point, unsigned int);
    bool isCoast(Point);
public:
    static MapGenerator* getInstance();
    
    /**
    delete all the statics elements
    **/
    void deleteInstance();

    /**
    only ocean
    add the seconde parameter to generate islands
    **/
    void generateMap(unsigned int sizeMap);

    /**
    add islands in the map
    remove the seconde parameter so as not to generate islands
    **/
    void generateMap(unsigned int sizeMap, unsigned int nbIslands);

    /**
    add markets in the map
    on the coast beaches by default or randomly
    **/
    void addMarketPlaces(unsigned int nbMarkets);
    void addWind();
    void addBoat();

    Map* getGeneratedMap();
};

#endif