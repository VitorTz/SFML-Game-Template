#include "../include/scene.hpp"
#include "../include/globals.hpp"
#include "../include/camera.hpp"
#include "../include/ecs.hpp"


og::LevelScene::LevelScene() {
    
}


void og::LevelScene::update(const float dt) {        
    og::gEcs.update(dt);
}


void og::LevelScene::draw(sf::RenderWindow& window) {
    og::Camera::beginDrawing(window);
        og::gEcs.draw(window);
    og::Camera::endDrawing(window);
}


void og::LevelScene::unload() {
    
}