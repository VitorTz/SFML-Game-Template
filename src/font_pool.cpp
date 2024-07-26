#include "../include/font.hpp"
#include "../include/logger.hpp"


std::map<og::FontId, sf::Font> og::FontPool::fontMap{};


void og::FontPool::init() {
    for (auto& pair : og::fontPath) {
        og::FontPool::fontMap.insert({pair.first, sf::Font()});
        if (og::FontPool::fontMap[pair.first].loadFromFile(pair.second) == false) {
            std::string errorMsg = "Font load fail: ";
            errorMsg += pair.second;
            og::Log::error(errorMsg);
        } 
    }   
}


sf::Text og::FontPool::getText(const og::FontId fontId) {
    sf::Text text{};
    text.setFont(og::FontPool::fontMap[fontId]);
    return text;
}


void og::FontPool::setText(sf::Text* text, const og::FontId fontId) {
    text->setFont(og::FontPool::fontMap[fontId]);
}


void og::FontPool::clear() {
    og::FontPool::fontMap.clear();
}