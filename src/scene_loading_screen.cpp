#include "../include/scene.hpp"
#include "../include/globals.hpp"


og::LoadingScreen::LoadingScreen() {

}


void og::LoadingScreen::update(const float dt) {

}

void og::LoadingScreen::draw(sf::RenderWindow& window) {
    window.clear(og::globals::windowBackgroundColor);
    window.display();
}


void og::LoadingScreen::unload() {
    
}