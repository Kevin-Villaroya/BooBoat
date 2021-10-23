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
    
    bool thereIsIslandNear(Point, unsigned int);
public:
    static MapGenerator* getInstance();
    
    void deleteInstance();

    void generateMap(unsigned int sizeMap, unsigned int nbIslands);
    void addMarketPlaces(unsigned int nbMarkets);
    void addWind();
    void addBoat();

    Map* getGeneratedMap();
};

#endif