#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include "components.hpp"


namespace og {


    unsigned long hash(const char* s);

    unsigned long timeInMiliseconds();
    
    void sleepSeconds(int seconds);

    void sleepMili(unsigned long mili);

    int randint(int start, int end);

    void normalizeVec(sf::Vector2f* v);

    template<typename T, std::size_t size>
    T& choiceArray(const std::array<T, size>& arr) {
        return arr[og::randint(0, arr.size() - 1)];
    }

    template<typename T>
    T& choiceVec(const std::vector<T>& arr) {
        return arr[og::randint(0, arr.size() - 1)];
    }

    void drawBorder(
        sf::RenderWindow& window, 
        const sf::FloatRect& rect,
        const sf::Color& color,
        const float thickness
    );

    void drawBorder(
        sf::RenderWindow& window, 
        const sf::Vector2f& pos,
        const sf::Vector2f& size,
        const sf::Color& color,
        const float thickness
    );

    void drawBorder(
        sf::RenderWindow& window,
        const og::transform_t& transform,
        const sf::Color& color,
        const float thickness
    );

    bool intersects(const og::transform_t& left, const og::transform_t& right);

    void printVec(const sf::Vector2f& vec);

    void printRect(const sf::FloatRect& rect);

    void printTransform(const og::transform_t& transform);
    

} // namespace og
