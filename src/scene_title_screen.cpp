#include "../include/scene.hpp"
#include "../include/globals.hpp"


og::TitleScreenScene::TitleScreenScene() {

}


void og::TitleScreenScene::update(const float dt) {
    og::SceneManager::requestSceneChange(og::SceneId::LevelSceneId);
}


void og::TitleScreenScene::draw(sf::RenderWindow& window) {
    
}