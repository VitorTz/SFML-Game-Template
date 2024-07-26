#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>


namespace og {

    class Debug {        

        private:
            sf::Text text{};
            sf::Vector2f pos{20.f, 20.f};
            std::stringstream strStream{};
            float yOffset = 20.0f;
            
        
        private:
            void drawText(sf::RenderWindow& window);
        
        public:            
            void init();
            void draw(sf::RenderWindow& window);
    };

    inline og::Debug gDebug{};
    
} // namespace og
