#include "../include/scene.hpp"
#include "../include/globals.hpp"
#include "../include/camera.hpp"
#include "../include/constants.hpp"
#include "../include/texture_pool.hpp"


og::LevelScene::LevelScene() {

}


void og::LevelScene::update(const float dt) {
    
}


void og::LevelScene::draw(sf::RenderWindow& window) {            
    og::Camera::beginDrawing(window);        
    og::Camera::endDrawing(window);    
}
