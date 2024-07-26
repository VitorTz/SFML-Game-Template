#pragma once
#include <SFML/Graphics.hpp>
#include "constants.hpp"


namespace og {


    class Camera {

        public:
            static sf::View view;
            static void beginDrawing(sf::RenderWindow& window);
            static void endDrawing(sf::RenderWindow& window);

    };
    
} // namespace og
