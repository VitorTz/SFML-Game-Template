#include "../include/scene.hpp"
#include "../include/logger.hpp"
#include <stdio.h>
#include <thread>


std::unique_ptr<og::Scene> og::SceneManager::scene = nullptr;
std::unique_ptr<og::LoadingScreen> og::SceneManager::loadingScreen = nullptr;
og::SceneId og::SceneManager::sceneId = og::SceneId::TitleScreenSceneId;
bool og::SceneManager::shouldChangeScene = false;
bool og::SceneManager::isChangingScene = false;


void og::SceneManager::init() {
    og::SceneManager::scene = std::make_unique<og::TitleScreenScene>();
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
        og::Log::log(
            "REQUEST TO CHANGE SCENE",
            og::LogLevel::INFO            
        );
        og::SceneManager::sceneId = sceneId;
        og::SceneManager::shouldChangeScene = true;
    }
}


void og::SceneManager::changeScene() {
    std::string sceneName{};
    switch (og::SceneManager::sceneId) {
        case og::SceneId::TitleScreenSceneId:
            og::SceneManager::scene = std::make_unique<og::TitleScreenScene>();
            sceneName = "TitleScreenScene";
            break;
        case og::SceneId::LevelSceneId:
            og::SceneManager::scene = std::make_unique<og::LevelScene>();
            sceneName = "levelScene";
            break;
        default:
            break;
    }
    og::Log::log("Scene Change to -> " + sceneName, og::INFO);
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