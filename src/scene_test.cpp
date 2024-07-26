#include "../include/scene.hpp"
#include "../include/ecs.hpp"
#include "../include/constants.hpp"
#include "../include/camera.hpp"
#include "../include/util.hpp"
#include <random>
#include <iostream>


std::default_random_engine generator;
std::uniform_real_distribution<float> randXpos(0.0f, og::SCREEN_WIDTH);
std::uniform_real_distribution<float> randYpos(0.0f, og::SCREEN_HEIGHT);
std::uniform_real_distribution<float> randSpeed(30.f, 150.f);


///////////////////////////// Teste Scene 1////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

og::TestScene1::TestScene1() {
    for (og::entity_t i = 0; i < og::MAX_ENTITIES; i++) {
        const og::entity_t e = og::gEcs.entityCreate(0, true);
        og::gEcs.addComponent<og::sprite_t>(e, og::sprite_t{ICON_IMAGE});
        og::gEcs.addComponent<og::obstacle_t>(e, og::obstacle_t{50.f, 50.f});
        og::transform_t& transform = og::gEcs.getComponent<og::transform_t>(e);
        transform.pos = { randXpos(generator), randYpos(generator) };
        this->entitySpeed[e] = randSpeed(generator);
    }
}


void og::TestScene1::update(const float dt) {
    og::SpriteSystem* spriteSystem = og::gEcs.getSystem<og::sprite_t, og::SpriteSystem>();
    for (const og::entity_t e : spriteSystem->entities) {
        og::transform_t& t = og::gEcs.getComponent<og::transform_t>(e);
        t.pos.y += dt * this->entitySpeed[e];
        if (t.pos.y + t.size.y > og::SCREEN_HEIGHT) {
            og::gEcs.entityDestroy(e);
        }
    }
    const unsigned long t1 = og::timeInMiliseconds();    
    og::gEcs.update(dt);
    std::cout << "Update time: " << og::timeInMiliseconds() - t1 << '\n';
}


void og::TestScene1::draw(sf::RenderWindow& window) {
    const unsigned long t1 = og::timeInMiliseconds();
    og::Camera::beginDrawing(window);
        og::gEcs.draw(window);
    og::Camera::endDrawing(window);
    std::cout << "Draw time: " << og::timeInMiliseconds() - t1 << '\n';
}


///////////////////////////// Teste Scene 1////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////




///////////////////////////// Teste Scene 2////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


og::TestScene2::TestScene2() {
    // enemy 
        this->enemyEntity = og::gEcs.entityCreate(0, true);        
        og::gEcs.addSprite(this->enemyEntity, sf::Vector2f(randXpos(generator), randYpos(generator)), ICON_IMAGE);        
        og::gEcs.addComponent<og::obstacle_t>(this->enemyEntity, og::obstacle_t{64.0f, 64.0f});

    // player
        this->playerEntity = og::gEcs.entityCreate(0, true);
        og::gEcs.addSprite(this->playerEntity, og::SCREEN_CENTER, ICON_IMAGE);        
}


void og::TestScene2::update(const float dt) {
    // player
        og::transform_t& playerTransform = og::gEcs.getTransform(this->playerEntity);
        sf::Vector2f direction = og::VECTOR_ZERO;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction.x = -1.0f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction.x = 1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction.y = -1.0f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction.y = 1.0f;
        }

        og::normalizeVec(&direction);        
        playerTransform.pos.x += dt * 150.f * direction.x;
        playerTransform.pos.y += dt * 150.f * direction.y;

    // enemy
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            og::transform_t& enemyTransform = og::gEcs.getTransform(this->enemyEntity);
            enemyTransform.pos = { randXpos(generator), randYpos(generator) };
        }


    og::gEcs.update(dt);
}


void og::TestScene2::draw(sf::RenderWindow& window) {    
    const og::obstacle_t& enemyObstacle = og::gEcs.getComponent<og::obstacle_t>(this->enemyEntity);
    const og::transform_t& enemyTransform = og::gEcs.getTransform(this->enemyEntity);
    const og::transform_t& playerTransform = og::gEcs.getTransform(this->playerEntity);
    
    const std::pair<float, og::entity_t> collision = og::gEcs.checkCollide(
        sf::FloatRect(playerTransform.pos.x, playerTransform.pos.y, playerTransform.size.x, playerTransform.size.y)
    );
    const std::pair<float, og::entity_t> collision1 = og::gEcs.checkCollideWithSystem<og::sprite_t>(this->playerEntity);

    sf::Color playerColor = collision1.first ? sf::Color::Magenta : sf::Color::Blue;
    playerColor = collision.first ? sf::Color::Red : playerColor;    
        
    og::Camera::beginDrawing(window);
        og::gEcs.draw(window);        

        // enemy collide box border
        og::drawBorder(
            window,
            enemyObstacle.rect,
            sf::Color::Green,
            2.0f
        );

        // enemy transform border
        og::drawBorder(
            window,
            enemyTransform,
            sf::Color::White,
            2.0f
        );

        // player transform border 
        og::drawBorder(
            window,
            playerTransform,            
            playerColor,
            2.0f
        );
        
    og::Camera::endDrawing(window);
}


///////////////////////////// Teste Scene 2////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////