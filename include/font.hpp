#pragma once
#include <string>
#include <map>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "constants.hpp"

namespace og {


    enum FontId {
        Light,
        Regular,
        Semibold,
        Bold
    };

    const static std::map<og::FontId, std::string> fontPath = {
        {og::FontId::Light, ASSETS_PATH "font/Poppins-Light.ttf"},
        {og::FontId::Regular, ASSETS_PATH "font/Poppins-Regular.ttf"},
        {og::FontId::Semibold, ASSETS_PATH "font/Poppins-SemiBold.ttf"},
        {og::FontId::Bold, ASSETS_PATH "font/Poppins-Bold.ttf"}
    };

    class FontPool {

        private:
            static std::map<og::FontId, sf::Font> fontMap;
                
        public:
            static void init();
            static sf::Text getText(og::FontId fontId);
            static void setText(sf::Text* text, og::FontId fontId);
            static void clear();

    };

    
} // namespace og
