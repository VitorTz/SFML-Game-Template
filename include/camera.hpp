#pragma once
#include <SFML/Graphics.hpp>
#include "constants.hpp"


namespace og {


    class Camera {

        private:
            static sf::Vector2f size;            
            static float zoom;

        private:
            static sf::View view;

        public:
            static sf::Vector2f getSize();
            static void setSize(sf::Vector2f size);            

            static sf::FloatRect getViewPort();
            static void setViewPort(const sf::FloatRect& rect);
            
            static float getZoom();
            static void setZoom(float zoom);
            static void zoomIn(float delta);
            static void zoomOut(float delta);
            
            static void move(float x, float y);
            static void move(const sf::Vector2f& distance);

            static void setTarget(const sf::Vector2f& target);
            static void setTarget(float x, float y);            
            static sf::Vector2f getTarget();

            static void beginDrawing(sf::RenderWindow& window);
            static void endDrawing(sf::RenderWindow& window);

    };
    
} // namespace og
