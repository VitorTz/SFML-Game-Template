#include "../include/texture_pool.hpp"
#include "../include/util.hpp"


std::map<unsigned long, sf::Texture> og::TexturePool::textureMap{};


sf::Texture* og::TexturePool::load(const char* fileName) {
    const unsigned long h = og::hash(fileName);
    if (og::TexturePool::textureMap.find(h) == og::TexturePool::textureMap.end()) {
        const auto& pair = og::TexturePool::textureMap.insert(
            {h, sf::Texture()}
        );
        pair.first->second.loadFromFile(fileName);
    }
    return &og::TexturePool::textureMap[h];
}


sf::Sprite og::TexturePool::getSprite(const char* fileName) {
    sf::Sprite sprite{};
    sf::Texture* t = og::TexturePool::load(fileName);
    sprite.setTexture(*t);
    return sprite;
}


void og::TexturePool::setSprite(sf::Sprite* sprite, const char* fileName) {
    sf::Texture* t = og::TexturePool::load(fileName);    
    sprite->setTexture(*t);
}


void og::TexturePool::erase(const char* fileName) {
    const unsigned long h = og::hash(fileName);
    og::TexturePool::textureMap.erase(h);
}


void og::TexturePool::clear() {
    og::TexturePool::textureMap.clear();
}


std::size_t og::TexturePool::size() {
    return og::TexturePool::textureMap.size();
}
