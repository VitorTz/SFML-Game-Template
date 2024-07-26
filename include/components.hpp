#pragma once
#include <SFML/Graphics.hpp>
#include "texture_pool.hpp"
#include "types.hpp"


namespace og {


    constexpr std::size_t NUM_COMPONENTS = 3;

    typedef struct transform {
        sf::Vector2f pos{};
        sf::Vector2f size{};
        og::zindex_t zindex{};
    } transform_t;

    typedef struct sprite_ {
        sf::Sprite sprite{};
        sf::Vector2f size{};
        sprite_() = default;
        sprite_(
            const char* fileName
        ) : sprite(og::TexturePool::getSprite(fileName)),
            size((sf::Vector2f) sprite.getTexture()->getSize()) {
                
        }
    } sprite_t; 

    typedef struct obstacle {
        sf::FloatRect rect{};
        sf::Vector2f collideScale{1.0f, 1.0f};
    } obstacle_t;

    
} // namespace og
