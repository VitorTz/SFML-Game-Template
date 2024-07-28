#include "../include/util.hpp"
#include <stdio.h>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>


unsigned long og::hash(const char* s) {
    unsigned long hash = 5381;
    int i = 0;
    while (s[i] != '\0') {
        int c = s[i];
        hash = ((hash << 5) + hash) + c;
        i++;
    }
    return hash;
}


int og::randint(const int start, const int end) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> d(start, end);
    return d(rng);
}


void og::sleepSeconds(const int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


void og::sleepMili(const unsigned long mili) {
    std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}


unsigned long og::timeInMiliseconds() {    
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return now_ms;
}


void og::normalizeVec(sf::Vector2f* v) {
    const float m = std::sqrt(v->x * v->x + v->y * v->y);
    if (m > 1) {
        v->x /= m;
        v->y /= m;
    }
}


void og::drawBorder(
    sf::RenderWindow& window,
    const sf::FloatRect& rect,
    const sf::Color& color,
    const float thickness
) {
    sf::RectangleShape r(sf::Vector2f(rect.width, rect.height));
    r.setPosition(rect.left, rect.top);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(color);
    r.setOutlineThickness(thickness);
    window.draw(r);
}


void og::drawBorder(
    sf::RenderWindow& window,
    const sf::Vector2f& pos,
    const sf::Vector2f& size,
    const sf::Color& color,
    const float thickness
) {
    sf::RectangleShape r(size);
    r.setPosition(pos);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(color);
    r.setOutlineThickness(thickness);
    window.draw(r);
}

void og::drawBorder(
    sf::RenderWindow& window,
    const og::transform_t& transform,
    const sf::Color& color,
    const float thickness
) {
    sf::RectangleShape r(sf::Vector2f(transform.size.x, transform.size.y));
    r.setPosition(transform.pos.x, transform.pos.y);
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineColor(color);
    r.setOutlineThickness(thickness);
    window.draw(r);
}


bool og::intersects(const og::transform_t& leftTransform, const og::transform_t& rightTransform) {
    const float r1MinX = std::min(leftTransform.pos.x, leftTransform.pos.x + leftTransform.size.x);
    const float r1MaxX = std::max(leftTransform.pos.x, leftTransform.pos.x + leftTransform.size.x);
    const float r1MinY = std::min(leftTransform.pos.y, leftTransform.pos.y + leftTransform.size.y);
    const float r1MaxY = std::max(leftTransform.pos.y, leftTransform.pos.y + leftTransform.size.y);
    
    const float r2MinX = std::min(rightTransform.pos.x, rightTransform.pos.x + rightTransform.size.x);
    const float r2MaxX = std::max(rightTransform.pos.x, rightTransform.pos.x + rightTransform.size.x);
    const float r2MinY = std::min(rightTransform.pos.y, rightTransform.pos.y + rightTransform.size.y);
    const float r2MaxY = std::max(rightTransform.pos.y, rightTransform.pos.y + rightTransform.size.y);
    
    const float interLeft   = std::max(r1MinX, r2MinX);
    const float interTop    = std::max(r1MinY, r2MinY);
    const float interRight  = std::min(r1MaxX, r2MaxX);
    const float interBottom = std::min(r1MaxY, r2MaxY);
    
    if ((interLeft < interRight) && (interTop < interBottom)) {        
        return true;
    } else {        
        return false;
    }
}


void og::printVec(const sf::Vector2f& vec) {
    printf("Vec(%.2f, %.2f)\n", vec.x, vec.y);
}


void og::printRect(const sf::FloatRect& rect) {
    printf("Vec(%.2f, %.2f, %.2f, %.2f)\n", rect.left, rect.top, rect.width, rect.height);
}


void og::printTransform(const og::transform_t& transform) {
    printf("Vec(%.2f, %.2f, %.2f, %.2f, %d)\n", transform.pos.x, transform.pos.x, transform.size.x, transform.size.y, transform.zindex);
}