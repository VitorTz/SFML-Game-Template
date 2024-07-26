#include "../include/system.hpp"
#include "../include/ecs.hpp"


void og::SpriteSystem::update(const float dt) {

}


void og::SpriteSystem::draw(
    sf::RenderWindow& window,
    const og::entity_t e
) {
    const og::transform_t& transform = og::gEcs.getComponent<og::transform_t>(e);
    og::sprite_t& sprite = og::gEcs.getComponent<og::sprite_t>(e);
    sprite.sprite.setPosition(transform.pos);
    window.draw(sprite.sprite);
}