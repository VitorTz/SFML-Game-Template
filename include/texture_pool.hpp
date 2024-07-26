#pragma once
#include <map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace og {


    class TexturePool {

        private:
            static std::map<unsigned long, sf::Texture> textureMap;

        private:
            static sf::Texture* load (const char* fileName);
            
        public:
            static void setSprite(sf::Sprite* sprite, const char* fileName);
            static sf::Sprite getSprite(const char* fileName);
            static void erase(const char* fileName);
            static void clear();
            static std::size_t size();

    };
    
} // namespace og
