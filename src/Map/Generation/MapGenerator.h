#ifndef __MAP_GENERATOR_H
#define __MAP_GENERATOR_H

#include "../Map.h"
#include "../../Common/Point.h"
#include "../Wind/Wind.h"

class MapGenerator{
private:
    static MapGenerator* instance;
    static Map* map;

    static const unsigned int SIZE_MIN_ISLAND;

    Point findNewIslandLocation(unsigned int minSize, unsigned int maxSize);
    void generateIsland(Point, unsigned int, unsigned int);

    std::vector<std::vector<std::pair<Point, int>>> makeGraph();
    void verifyConnexity();
    void resolveConnexityGraph(std::vector<std::vector<std::pair<Point, int>>>& graph, Point point);
    void setMapConnex(std::vector<std::vector<std::pair<Point, int>>>& graph);
    bool thereIsIslandNear(Point, unsigned int);

    std::vector<Point> getAllCoasts();
    unsigned int addMarketPlacesOnCoast(std::vector<Point>, unsigned int);
    void addMarketPlacesRandomly(unsigned int);
    bool isCoast(Point);
    void setHarbor(Point, Case*);

    Point findNewCenterWind(unsigned int);
    void generateWind(Point, unsigned);
    Direction getRandomDirection();
    bool thereIsWindNear(Point, int);
    
public:
    static MapGenerator* getInstance();

    /**
    delete all the statics elements
    **/
    void deleteInstance();

    /**
    set seed for all the simulation
    **/
    void setSeed(unsigned int seed);

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
    only ocean
    add the seconde parameter to generate islands
    **/
    void generateMap(unsigned int sizeMap, unsigned int nbIslands, unsigned int seed);

    /**
    add markets in the map
    on the coast beaches by default or randomly
    **/
    void addMarketPlaces(unsigned int nbMarkets);

    /**
    add wind in the map
    independently if it's a land or not
    **/
    void addWinds(unsigned int);

    /**
    add a boat in the map
    randomly placed on a water case
    **/
    void addBoat();

    Map* getGeneratedMap();
};

#endif