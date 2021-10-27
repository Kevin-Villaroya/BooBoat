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

void MapGenerator::generateMap(unsigned int sizeMap){
    delete MapGenerator::map;

    srand(time(NULL));

    MapGenerator::map = new Map(sizeMap);
}

void MapGenerator::generateMap(unsigned int sizeMap, unsigned int nbIslands){
    this->generateMap(sizeMap);
    
    unsigned int sizeMinIsland = std::max(MapGenerator::SIZE_MIN_ISLAND, (sizeMap / 5 ) / nbIslands);
    unsigned int sizeMaxIsland = std::max(sizeMinIsland, (sizeMap) / nbIslands);

    for(unsigned int i = 0; i < nbIslands; i++){
        Point location = this->findNewIslandLocation(sizeMinIsland, sizeMaxIsland);
        this->genereateIsland(location, sizeMinIsland, sizeMaxIsland);
    }

    this->verifyConnexity();
}

void MapGenerator::addMarketPlaces(unsigned int nbMarkets){
    std::vector<Point> coastPossible;

    coastPossible = this->getAllCoasts();

    unsigned int marketPlaces = this->addMarketPlacesOnCoast(coastPossible, nbMarkets);

    if(marketPlaces < nbMarkets){
        this->addMarketPlacesRandomly(nbMarkets - marketPlaces);
    }
}

void MapGenerator::addWinds(unsigned int nbWinds){
    unsigned int maxSize = MapGenerator::map->getSize() / (int)(nbWinds * 0.75);

    for(unsigned int i = 0; i < nbWinds; i++){
        Point windPos = this->findNewCenterWind(maxSize);
        this->generateWind(windPos, maxSize);
    }
}

void MapGenerator::addBoat(){
    std::vector<Point> possibleCase;
    for(unsigned int i = 0; i < MapGenerator::map->getSize(); i++){
        for(unsigned int j = 0; j < MapGenerator::map->getSize(); j++){
            Case* c = MapGenerator::map->caseAt(Point(i, j));
            if(c->isThrowable()){
                possibleCase.push_back(Point(i,j));
            }
        }
    }

    Point p = possibleCase[rand() % possibleCase.size()];
    MapGenerator::map->boat(new Boat(p));
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

std::vector<Point> MapGenerator::getAllCoasts(){
    std::vector<Point> coastPossible;

    for(unsigned int i = 0; i < MapGenerator::map->getSize(); i++){
        for(unsigned int j = 0; j < MapGenerator::map->getSize(); j++){
            if( isCoast(Point(i, j)) ){
                coastPossible.push_back(Point(i, j));
            }
        }
    }

    return coastPossible;
} 

unsigned int MapGenerator::addMarketPlacesOnCoast(std::vector<Point> coastPossible, unsigned int nbMarkets){
    unsigned int coastAdded = 0;

    for(unsigned int i = 0; i < nbMarkets; i++){
        unsigned int posInPossibilities = rand() % coastPossible.size();
        
        Point p = coastPossible[posInPossibilities];
        CaseIsland* newCase = new CaseIsland(p);

        newCase->putMarket();
        this->map->setCase(p, newCase);

        coastPossible.erase(coastPossible.begin() + posInPossibilities);
        coastAdded++;
    }

    return coastAdded;
}

void MapGenerator::addMarketPlacesRandomly(unsigned int nbMarkets){
    bool find = false;

    unsigned int coastAdded = 0;

    while(coastAdded < nbMarkets){
        find = false;

        while(!find){
            unsigned int posX = rand() % this->map->getSize();
            unsigned int posY = rand() % this->map->getSize();

            Case* c = this->map->caseAt(Point(posX, posY));
            if(c->isThrowable() && c->hasMarket()){
                CaseIsland* newCase = new CaseIsland(Point(posX, posY));
                newCase->putMarket();
                
                this->map->setCase(Point(posX, posY), newCase);

                find = true;
            }
        }

        coastAdded++;
    }
}

Point MapGenerator::findNewCenterWind(unsigned int maxSize){
    std::vector<Point> possibleCase;

    for(unsigned int i = 0; i < MapGenerator::map->getSize(); i++){
        for(unsigned int j = 0; j < MapGenerator::map->getSize(); j++){

            if( !thereIsWindNear(Point(i, j), maxSize) ){
                possibleCase.push_back(Point(i, j));
            }

        }
    }

    Point p = possibleCase[rand() % possibleCase.size()];

    return p;
}

void MapGenerator::generateWind(Point point, unsigned int maxSize){
    Wind* wind = new Wind(this->getRandomDirection());
    this->map->addWind(wind);

    unsigned int minSize = maxSize * 0.75;

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
                
                Point actual{(int)i, (int)j};

                if(random > chanceOfSpawn){
                    if(!this->map->outOfBounds(actual)){
                        if(!this->map->caseAt(actual)->hasWind()){
                            LocalWind* lw = new LocalWind(wind);
                            this->map->caseAt(actual)->wind(lw);
                            wind->addLocalWind(lw);
                        }
                    }
                }
            }
        }
    }
}

Direction MapGenerator::getRandomDirection(){
    unsigned int random = rand() % 8;

    switch (random){
    case 0:
        return Direction::East;
        break;
    case 1:
        return Direction::SouthEast;
        break;
    case 2:
        return Direction::South;
        break;
    case 3:
        return Direction::SouthWest;
        break;
    case 4:
        return Direction::West;
        break;
    case 5:
        return Direction::NorthWest;
        break;
    case 6:
        return Direction::North;
        break;
    case 7:
        return Direction::NorthEast;
        break;
    default:
        return Direction::None;
        break;
    }
}

bool MapGenerator::thereIsWindNear(Point p, int size){
    for(int i = -size ; i < size; i++){
        for(int j = -size; j < size; j++){
            Point actual{p.x + i, p.y + j};

            if( !MapGenerator::map->outOfBounds(actual) && abs(i + j) < size + 1){
                if( MapGenerator::map->caseAt(actual)->hasWind() ){
                    return true;
                }
            }
        }
    }

    return false;
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

bool MapGenerator::isCoast(Point p){
    if(!this->map->caseAt(p)->isThrowable()){
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                Point currentPoint{p.x + i, p.y + j};

                if(abs(i + j) == 1 && !this->map->outOfBounds(currentPoint)){
                    if(this->map->caseAt(currentPoint)->isThrowable()){
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
}