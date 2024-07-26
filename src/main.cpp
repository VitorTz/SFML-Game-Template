#include "../include/component_id_manager.hpp"
#include "../include/constants.hpp"
#include "../include/scene.hpp"
#include "../include/globals.hpp"
#include "../include/exit.hpp"
#include "../include/logger.hpp"
#include "../include/font.hpp"
#include "../include/ecs.hpp"
#include "../include/debug.hpp"


int main(int argc, char const *argv[]) {
    sf::RenderWindow window(
        sf::VideoMode(og::SCREEN_WIDTH, og::SCREEN_HEIGHT),
        og::WINDOW_TITLE,
        sf::Style::Close | sf::Style::Titlebar
    );
    
    window.setFramerateLimit(og::FPS);
    sf::Image iconImage;
    iconImage.loadFromFile(ICON_IMAGE);
    window.setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

    sf::Clock clock{};

    og::Log::init();
    
    if (og::TYPE_ID_MAP.size() != og::NUM_COMPONENTS) {
        og::Log::error("TYPE ID MAP SIZE != NUM_COMPONENTS");
    }

    og::FontPool::init();
    og::gEcs.init();
    og::gDebug.init();
    og::SceneManager::init();

    while (window.isOpen()) {

        if (!og::globals::gameIsRunning) {
            window.close();
            break;
        }
        const float dt = clock.restart().asSeconds();    
        
        sf::Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
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

    return 0;
}
