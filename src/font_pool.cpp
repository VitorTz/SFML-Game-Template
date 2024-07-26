#include "../include/font.hpp"


std::map<og::FontId, sf::Font> og::FontPool::fontMap{};


void og::FontPool::init() {
    for (auto& pair : og::fontPath) {
        og::FontPool::fontMap.insert({pair.first, sf::Font()});
        og::FontPool::fontMap[pair.first].loadFromFile(pair.second);
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