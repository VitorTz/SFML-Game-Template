#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <unordered_set>
#include "types.hpp"


namespace og {

    class System {

        public:
            std::unordered_set<og::entity_t> entities{};

        public:
            virtual ~System() = default;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window, og::entity_t e) = 0;

    };

    
    class SpriteSystem : public og::System {

        public:
            void update(float dt) override;
            void draw(sf::RenderWindow& window, og::entity_t e) override;

    };

    class ObstacleSystem : public og::System {

        public:
            void update(float dt) override;
            void draw(sf::RenderWindow& window, og::entity_t e) override;

    };
    
} // namespace og
