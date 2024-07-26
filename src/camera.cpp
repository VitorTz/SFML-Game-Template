#include "../include/camera.hpp"


sf::View og::Camera::view = sf::View(og::SCREEN_CENTER, og::SCREEN_SIZE);


void og::Camera::beginDrawing(
    sf::RenderWindow& window
) {
    window.setView(og::Camera::view);
}


void og::Camera::endDrawing(
    sf::RenderWindow& window
) {
    window.setView(og::Camera::view);
}