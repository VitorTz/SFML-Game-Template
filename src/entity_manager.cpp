#include "../include/entity_manager.hpp"
#include <cassert>


og::EntityManager::EntityManager() {
    for (og::entity_t e = 0; e < og::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
}


og::entity_t og::EntityManager::entityCreate() {
    assert(this->mSize < og::MAX_ENTITIES);
    const og::entity_t e = this->queue.front();
    this->queue.pop();
    this->mSize++;
    return e;
}


void og::EntityManager::entityDestroy(const og::entity_t e) {
    this->queue.push(e);
    this->mSize--;
}


void og::EntityManager::clear() {
    this->queue = std::queue<og::entity_t>();
    for (og::entity_t e = 0; e < og::MAX_ENTITIES; e++) {
        this->queue.push(e);
    }
    this->mSize = 0;
}


std::size_t og::EntityManager::size() const {
    return this->mSize;
}