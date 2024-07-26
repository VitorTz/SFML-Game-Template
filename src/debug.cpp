#include "../include/debug.hpp"
#include "../include/font.hpp"
#include "../include/ecs.hpp"
#include "../include/constants.hpp"
#include "../include/camera.hpp"
#include <iostream>
#include <stdio.h>


void og::Debug::init() {
    og::FontPool::setText(&this->text, og::FontId::Regular);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(14);
    this->background.setFillColor(og::colors::BLACK_TRANSPARENT);
    this->background.setPosition({14.f, 18.f});
    this->background.setSize({120.f, 140.0f});
}


void og::Debug::drawText(sf::RenderWindow& window) {    
    this->text.setString(this->strStream.str());
    this->text.setPosition(this->pos);
    window.draw(this->text);
    this->pos.y += this->yOffset;
    this->strStream = std::stringstream();    
}


void og::Debug::draw(sf::RenderWindow& window) {
    if (og::DEBUD_MODE) {
        window.draw(this->background);
        this->pos = {20.0f, 20.0f};
        this->strStream << "Zoom: " << og::Camera::getZoom();
        this->drawText(window);
        this->strStream << "Entity: " << og::gEcs.numEntities();
        this->drawText(window);
        this->strStream << "Component: " << og::gEcs.numComponents();
        this->drawText(window);
        this->strStream << "System: " << og::gEcs.numComponents();
        this->drawText(window);
    }
}