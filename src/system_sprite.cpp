#include "../include/system.hpp"
#include "../include/ecs.hpp"
#include "../include/globals.hpp"
#include <cmath>


void og::SpriteSystem::update(const float dt) {

}


void og::SpriteSystem::draw(
    sf::RenderWindow& window,
    const og::entity_t e
) {
    const og::transform_t& transform = og::gEcs.getTransform(e);
    og::sprite_t& sprite = og::gEcs.getComponent<og::sprite_t>(e);
    sprite.sprite.setPosition(transform.pos.x, transform.pos.y);    
    window.draw(sprite.sprite);
}