#include "Engine.h"
#include <iostream>
#include <thread>
#include <chrono>

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
        this->update();
    }
}

void Engine::render(){
    this->window->clear(sf::Color::Black);

    Point posBoat = this->map->boat()->pos();

    for(unsigned int i = 0; i < this->map->getSize(); i++){
        for(unsigned int j = 0; j < this->map->getSize(); j++){

            this->window->draw(*this->map->caseAt(Point(i, j)));
            Case* c = this->map->caseAt(Point(i, j));

            if( c->hasWind() ){
                this->window->draw( *this->map->caseAt(Point(i, j))->wind() );
            }

            if(posBoat.x == (int)i && posBoat.y == (int)j){
                this->window->draw( *this->map->boat() );
            }
        }
    }

    this->window->display();
}

void Engine::update(){
    using namespace std::literals;

    this->map->tick();
    std::this_thread::sleep_for(1s);
}