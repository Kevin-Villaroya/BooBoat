#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "SFML/Graphics.hpp"
#include "../Map/Map.h"

class Engine{
private:
    sf::RenderWindow* window;

    unsigned int width = 1080;
    unsigned int height = 1080;

    Map* map;

public:
    Engine(Map*);
    Engine(unsigned int sizeXScreen, unsigned int sizeYScreen, Map*);

    ~Engine();

    void run();
    void checkEvent();
    void render();
};

#endif