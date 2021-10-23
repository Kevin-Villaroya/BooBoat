#include "MapGenerator.h"
#include "../Case/CaseIsland.h"
#include "../Case/CaseWater.h"

#include <math.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <map>

MapGenerator* MapGenerator::instance = nullptr;
Map* MapGenerator::map = nullptr;
const unsigned int MapGenerator::SIZE_MIN_ISLAND = 2;

MapGenerator* MapGenerator::getInstance(){
    if(MapGenerator::instance == nullptr){
        MapGenerator::instance = new MapGenerator();
        MapGenerator::map = new Map();
    }

    return MapGenerator::instance;
}

void MapGenerator::deleteInstance(){
    delete MapGenerator::instance;
    delete MapGenerator::map;
}

void MapGenerator::generateMap(unsigned int sizeMap, unsigned int nbIslands){
    delete map;

    srand(time(NULL));

    unsigned int sizeMinIsland = std::max(MapGenerator::SIZE_MIN_ISLAND, (sizeMap / 5 ) / nbIslands);
    unsigned int sizeMaxIsland = std::max(sizeMinIsland, (sizeMap) / nbIslands);

    MapGenerator::map = new Map(sizeMap);

    for(unsigned int i = 0; i < nbIslands; i++){
        Point location = this->findNewIslandLocation(sizeMinIsland, sizeMaxIsland);
        this->genereateIsland(location, sizeMinIsland, sizeMaxIsland);
    }

    this->verifyConnexity();
}

void MapGenerator::addMarketPlaces(unsigned int nbMarkets){

}

void MapGenerator::addWind(){

}

void MapGenerator::addBoat(){

}

Map* MapGenerator::getGeneratedMap(){
    return this->map;
}

Point MapGenerator::findNewIslandLocation(unsigned int minSize, unsigned int maxSize){
    std::vector<Point> possibleCase;

    for(unsigned int i = 0; i < MapGenerator::map->getSize(); i++){
        for(unsigned int j = 0; j < MapGenerator::map->getSize(); j++){
            if( !thereIsIslandNear(Point(i, j), maxSize) ){
                possibleCase.push_back(Point(i, j));
            }
        }
    }

    Point p = possibleCase[rand() % possibleCase.size()];
    return p;
}

void MapGenerator::genereateIsland(Point point, unsigned int minSize, unsigned int maxSize){

    for(unsigned int i = point.x; i < point.x + maxSize; i++){
        for(unsigned int j = point.y; j < point.y + maxSize; j++){
            unsigned int random = rand() % 100 + 1;

            if(i < minSize){
                MapGenerator::map->setCase(Point(i, j), new CaseIsland(Point(i, j)));
            }else{
                unsigned int chanceOfSpawn = 100;
                unsigned int differenceMaxMin = maxSize - minSize;

                if( i < minSize + differenceMaxMin * 1.25 ){
                    chanceOfSpawn = 75;
                }else if( i < minSize + differenceMaxMin * 1.5 ){
                    chanceOfSpawn = 50;
                }else if( i < minSize + differenceMaxMin * 1.75 ){
                    chanceOfSpawn = 25;
                }else{
                    chanceOfSpawn = 10;
                }
                
                if(random > chanceOfSpawn){
                    MapGenerator::map->setCase(Point(i, j), new CaseIsland(Point(i, j)));
                }else{
                    MapGenerator::map->setCase(Point(i, j), new CaseWater(Point(i, j)));
                }
            }
        }
    }
}

std::vector<std::vector<std::pair<Point, int>>> MapGenerator::makeGraph(){
    std::vector<std::vector<std::pair<Point, int>>> graph;

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        std::vector<std::pair<Point, int>> graphLine;

        for(unsigned int j = 0; j < this->map->getSize(); j++){
            std::pair<Point, int> caseInGraph;

            if( this->map->caseAt(Point(i, j))->isThrowable() ){
                caseInGraph.first = Point(i, j);
                caseInGraph.second = i + j;
            }else{
                caseInGraph.first = Point(i, j);
                caseInGraph.second = -1;
            }
            
            graphLine.push_back(caseInGraph);
        }
        graph.push_back(graphLine);
    } 

    return graph;
}

void MapGenerator::verifyConnexity(){
    std::vector<std::vector<std::pair<Point, int>>> graph = makeGraph();

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        for(unsigned int j = 0; j < this->map->getSize(); j++){
            if(this->map->caseAt(Point(i, j))->isThrowable()){
                resolveConnexityGraph(graph, Point(i, j));
            }
        }
    }

    this->setMapConnex(graph);
}

void MapGenerator::resolveConnexityGraph(std::vector<std::vector<std::pair<Point, int>>>& graph, Point point){
    int valueGraph = graph[point.x][point.y].second;

    int newValue = valueGraph;

    if(valueGraph != -1){
        for(int i = -1 ; i < 2; i++){
            for(int j = -1 ; j < 2; j++){
                Point actual = Point(point.x + i, point.y + j);

                if( !this->map->outOfBounds(actual) && abs(i + j) == 1){
                    if(graph[actual.x][actual.y].second != -1 && graph[actual.x][actual.y].second < newValue){
                        newValue = graph[actual.x][actual.y].second;
                    }
                }
            } 
        }

        if(newValue < graph[point.x][point.y].second){
            graph[point.x][point.y].second = newValue;
            for(int i = -1 ; i < 2; i++){
                for(int j = -1 ; j < 2; j++){
                    Point actual = Point(point.x + i, point.y + j);

                    if(!this->map->outOfBounds(actual) && abs(i + j) == 1){
                        resolveConnexityGraph(graph, actual);
                    }                    
                }
            }   
        }
    }
    
}

void MapGenerator::setMapConnex(std::vector<std::vector<std::pair<Point, int>>>& graph){
    std::map<unsigned int, int> nbSubGraphsConnex;

    int graphName = 0;
    int nbGraph = 0;

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        for(unsigned int j = 0; j < this->map->getSize(); j++){
            if(graph[i][j].second != -1){
                nbSubGraphsConnex[graph[i][j].second] += 1;
            }
        }
    }

    for (const auto &[nameGraph, count] : nbSubGraphsConnex) {
        if(nbGraph < count){
            graphName = nameGraph;
            nbGraph = count;
        }
    }

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        for(unsigned int j = 0; j < this->map->getSize(); j++){
            if(graph[i][j].second != graphName && graph[i][j].second != -1){
                this->map->setCase(Point(i, j), new CaseIsland(Point(i, j)));
            }
        }
    }
}

bool MapGenerator::thereIsIslandNear(Point point, unsigned int size){
    for(unsigned int i = point.x - size ; i < point.x + size; i++){
        for(unsigned int j = point.y - size; j < point.y + size; j++){
            if( !MapGenerator::map->outOfBounds(Point(i, j)) ){
                if( !MapGenerator::map->caseAt(Point(i, j))->isThrowable() ){
                    return true;
                }
            }
        }
    }

    return false;
}

