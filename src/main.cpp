#include "../include/component_id_manager.hpp"
#include "../include/constants.hpp"
#include "../include/scene.hpp"
#include "../include/globals.hpp"
#include "../include/exit.hpp"
#include "../include/logger.hpp"
#include "../include/font.hpp"
#include "../include/ecs.hpp"
#include "../include/camera.hpp"
#include "../include/debug.hpp"


int main(int argc, char const *argv[]) {
    // window init
    sf::RenderWindow window(
        sf::VideoMode(og::SCREEN_WIDTH, og::SCREEN_HEIGHT),
        og::WINDOW_TITLE,
        sf::Style::Close | sf::Style::Titlebar
    );
    
    window.setFramerateLimit(og::FPS);
    
    og::Log::init();
    
    // icon
    sf::Image iconImage;
    if (!iconImage.loadFromFile(ICON_IMAGE)) {
        og::Log::error("ICON IMAGE NOT FOND");
        return EXIT_FAILURE;
    }
    window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

    sf::Clock clock{};

    
    if (og::TYPE_ID_MAP.size() != og::NUM_COMPONENTS) {
        og::Log::error("TYPE ID MAP SIZE != NUM_COMPONENTS");
        return EXIT_FAILURE;
    }

    og::FontPool::init();
    og::gEcs.init();
    og::gDebug.init();
    og::SceneManager::init();    

    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();
        sf::Event e{};

        if (!og::globals::gameIsRunning) {
            window.close();
            break;
        }

        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseWheelMoved: 
                    og::Camera::zoomIn(e.mouseWheel.delta * og::CAMERA_ZOOM_SPEED * dt);                    
                    break;
                default:
                    break;
            }
        }

        og::SceneManager::update(dt);
        window.clear(og::globals::windowBackgroundColor);
            og::SceneManager::draw(window);
            og::gDebug.draw(window);
        window.display();
    }

    og::exitGame();

    return EXIT_SUCCESS;
}
