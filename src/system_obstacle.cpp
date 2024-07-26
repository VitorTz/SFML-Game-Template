#include "../include/system.hpp"
#include "../include/ecs.hpp"


void og::ObstacleSystem::update(const float dt) {        
    for (const og::entity_t e : this->entities) {
        const og::transform_t& t = og::gEcs.getTransform(e);
        og::obstacle_t& o = og::gEcs.getComponent<og::obstacle_t>(e);
        o.rect.left = t.pos.x + t.size.x / 2.0f - o.rect.width / 2.0f;
        o.rect.top = t.pos.y + t.size.y - o.rect.height;
    }
}


void og::ObstacleSystem::draw(sf::RenderWindow& window, const og::entity_t e) {

}