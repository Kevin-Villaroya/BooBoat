#include "Engine.h"
#include <iostream>

Engine::Engine(Map* map) : Engine(720, 720, map){}

Engine::Engine(unsigned int sizeXScreen, unsigned int sizeYScreen, Map* map){
    this->window = new sf::RenderWindow(sf::VideoMode(sizeXScreen, sizeYScreen), "Boat Bot");
    this->map = map;
}

Engine::~Engine(){
    delete this->window;
}

void Engine::checkEvent(){
    sf::Event event;

        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
        }
}

void Engine::run(){
    while (window->isOpen()){
        this->checkEvent();
        this->render();
    }
}

void Engine::render(){
    this->window->clear(sf::Color::Black);

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        for(unsigned int j = 0; j < this->map->getSize(); j++){
            this->window->draw(*this->map->caseAt(Point(i, j)));
            if( this->map->caseAt(Point(i, j))->hasWind() ){
                this->window->draw( *this->map->caseAt(Point(i, j))->wind() );
            }
        }
    }

    this->window->display();
}