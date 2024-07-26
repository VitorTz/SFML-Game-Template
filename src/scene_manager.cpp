#include "../include/scene.hpp"
#include "../include/logger.hpp"
#include "../include/constants.hpp"
#include <stdio.h>
#include <thread>


std::unique_ptr<og::Scene> og::SceneManager::scene = nullptr;
std::unique_ptr<og::LoadingScreen> og::SceneManager::loadingScreen = nullptr;
og::SceneId og::SceneManager::sceneId = og::FIRST_SCENE;
bool og::SceneManager::shouldChangeScene = false;
bool og::SceneManager::isChangingScene = false;


void og::SceneManager::init() {    
    og::SceneManager::loadNextScene();
    og::SceneManager::loadingScreen = std::make_unique<og::LoadingScreen>();
}


void og::SceneManager::update(const float dt) {
    if (og::SceneManager::isChangingScene) {
        og::SceneManager::loadingScreen->update(dt);
    } else {
        og::SceneManager::scene->update(dt);
    }
}


void og::SceneManager::requestSceneChange(const og::SceneId sceneId) {
    if (
        og::SceneManager::shouldChangeScene == false &&
        og::SceneManager::isChangingScene == false
    ) {
        og::Log::log("REQUEST TO CHANGE SCENE", og::LogLevel::INFO);
        og::SceneManager::sceneId = sceneId;
        og::SceneManager::shouldChangeScene = true;
    }
}

void og::SceneManager::loadNextScene() {    
    switch (og::SceneManager::sceneId) {
        case og::SceneId::TitleScreenSceneId:
            og::SceneManager::scene = std::make_unique<og::TitleScreenScene>();            
            break;
        case og::SceneId::LevelSceneId:
            og::SceneManager::scene = std::make_unique<og::LevelScene>();            
            break;
        case og::SceneId::TestScene1Id:
            og::SceneManager::scene = std::make_unique<og::TestScene1>();            
            break;
        case og::SceneId::TestScene2Id:
            og::SceneManager::scene = std::make_unique<og::TestScene2>();
            break;
        default:
            break;
    }
}


void og::SceneManager::changeScene() {
    og::SceneManager::loadNextScene();
    og::Log::log("Scene Change to -> " + std::to_string(og::SceneManager::sceneId), og::INFO);
    og::SceneManager::isChangingScene = false;
}


void og::SceneManager::draw(sf::RenderWindow& window) {
    if (og::SceneManager::isChangingScene) {
        og::SceneManager::loadingScreen->draw(window);
    } else {
        og::SceneManager::scene->draw(window);
    }
    if (og::SceneManager::shouldChangeScene) {
        og::SceneManager::shouldChangeScene = false;
        og::SceneManager::isChangingScene = true;
        std::thread t(&og::SceneManager::changeScene);
        t.detach();
    }
}