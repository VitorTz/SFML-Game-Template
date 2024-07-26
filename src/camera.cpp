#include "../include/camera.hpp"
#include <cmath>


sf::View og::Camera::view = sf::View(og::SCREEN_CENTER, og::SCREEN_SIZE);
sf::Vector2f og::Camera::size = og::SCREEN_SIZE;
float og::Camera::zoom = 1.0f;


void og::Camera::beginDrawing(
    sf::RenderWindow& window
) {
    window.setView(og::Camera::view);
}


void og::Camera::endDrawing(
    sf::RenderWindow& window
) {
    window.setView(window.getDefaultView());
}


sf::Vector2f og::Camera::getSize() {
    return og::Camera::size;
}

void og::Camera::setSize(sf::Vector2f size) {
    og::Camera::size = size;
    og::Camera::view.setSize(size);
}


void og::Camera::setZoom(const float zoom) {
    float z = std::clamp(zoom, og::CAMERA_MIN_ZOOM, og::CAMERA_MAX_ZOOM);
    og::Camera::setSize(og::Camera::size);
    og::Camera::view.zoom(z);
    og::Camera::zoom = z;
} 


float og::Camera::getZoom() {
    return og::Camera::zoom;
}


void og::Camera::zoomIn(const float delta) {
    og::Camera::setZoom(og::Camera::zoom + delta);
}


void og::Camera::zoomOut(const float delta) {
    og::Camera::setZoom(og::Camera::zoom - delta);
}


void og::Camera::setTarget(const sf::Vector2f& target) {
    og::Camera::view.setCenter(target);
}


void og::Camera::setTarget(const float x, const float y) {
    og::Camera::view.setCenter(x, y);
}


void og::Camera::move(const float x, const float y) {
    og::Camera::move(x, y);
}


void og::Camera::move(const sf::Vector2f& distance) {
    og::Camera::move(distance);    
}


sf::FloatRect og::Camera::getViewPort() {
    return og::Camera::view.getViewport();
}


void og::Camera::setViewPort(const sf::FloatRect& rect) {
    og::Camera::view.setViewport(rect);
}


sf::Vector2f og::Camera::getTarget() {
    return og::Camera::view.getCenter();
}
