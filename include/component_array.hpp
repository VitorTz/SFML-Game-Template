#pragma once
#include <array>
#include <unordered_map>
#include <cassert>
#include "constants.hpp"
#include "types.hpp"


namespace og {

    class IComponentArray {

        public:
            virtual ~IComponentArray() = default;
            virtual og::entity_t getEntityAtIndex(const std::size_t i) = 0;
            virtual void erase(og::entity_t e) = 0;
            virtual void clear() = 0;
            virtual std::size_t size() const = 0;

    };

    template<typename T>
    class ComponentArray : public og::IComponentArray {

        private:
            std::array<T, og::MAX_ENTITIES> arr{};
            std::unordered_map<og::entity_t, std::size_t> entityToIndex{};
            std::unordered_map<std::size_t, og::entity_t> indexToEntity{};
            std::size_t mSize = 0;

        public:

            ComponentArray() {
                this->entityToIndex.reserve(og::MAX_ENTITIES);
                this->indexToEntity.reserve(og::MAX_ENTITIES);
            }

            void insert(const og::entity_t e, T c) {
                this->entityToIndex[e] = this->mSize;
                this->indexToEntity[this->mSize] = e;
                this->arr[this->mSize++] = c;
            }

            const std::array<T, og::MAX_ENTITIES>& getArray() {
                return this->arr;
            }

            og::entity_t getEntityAtIndex(const std::size_t i) {
                assert(this->indexToEntity.find(i) != this->indexToEntity.end());
                return this->indexToEntity[i];
            }

            void erase(const og::entity_t e) override {
                if (this->entityToIndex.find(e) == this->entityToIndex.end()) {
                    return;
                }
                const std::size_t lastComponentIndex = --this->mSize;
                const std::size_t removedComponentIndex = this->entityToIndex[e];
                const og::entity_t lastEntity = this->indexToEntity[lastComponentIndex];
                
                this->arr[removedComponentIndex] = this->arr[lastComponentIndex];

                this->entityToIndex[lastEntity] = removedComponentIndex;
                this->indexToEntity[removedComponentIndex] = lastEntity;

                this->entityToIndex.erase(e);
                this->indexToEntity.erase(lastComponentIndex);
            }

            void clear() override {
                this->entityToIndex.clear();
                this->indexToEntity.clear();
                this->mSize = 0;
            }

            T& at(const og::entity_t e) {
                assert(this->entityToIndex.find(e) != this->entityToIndex.end());
                return this->arr[this->entityToIndex[e]];
            }

            std::size_t size() const override {
                return this->mSize;
            }

    };
    
} // namespace og

