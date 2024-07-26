#pragma once
#include <unordered_map>
#include <memory>
#include "logger.hpp"
#include "constants.hpp"
#include "components.hpp"
#include "component_id_manager.hpp"
#include "system.hpp"


namespace og {

    class SystemManager {

        private:
            std::unordered_map<og::component_id_t, std::unique_ptr<og::System>> systemMap{};
            std::unordered_map<og::entity_t, std::unordered_set<og::component_id_t>> entityToSystem{};
            std::array<og::component_id_t, og::NUM_COMPONENTS - 1> systemOrder{
                og::getComponentId<og::sprite_t>(),
                og::getComponentId<og::obstacle_t>()
            };
        
        private:
            template<typename T, typename S>
            void registerSystem() {
                this->systemMap.emplace(og::getComponentId<T>(), std::make_unique<S>());
            }
        
        public:
            SystemManager() {
                this->registerSystem<og::sprite_t, og::SpriteSystem>();
                this->registerSystem<og::obstacle_t, og::ObstacleSystem>();
                if (this->systemMap.size() != og::NUM_COMPONENTS - 1) {
                    og::Log::error("SystemMap size != NUM_COMPONENTS");
                }
                for (auto& pair : this->systemMap) {
                    pair.second->entities.reserve(og::MAX_ENTITIES);
                }
                for (auto& pair : this->entityToSystem) {
                    pair.second.reserve(og::MAX_ENTITIES);
                }                
            }

            template<typename T>
            void insert(const og::entity_t e) {
                const og::component_id_t id = og::getComponentId<T>();
                this->systemMap[id]->entities.insert(e);
                this->entityToSystem[e].insert(id);
            }

            template<typename T>
            void erase(const og::entity_t e) {
                const og::component_id_t id = og::getComponentId<T>();
                this->systemMap[id]->entities.erase(e);
                this->entityToSystem[e].erase(id);
            }

            template<typename T, typename S>
            S* getSystem() {
                const og::component_id_t id = og::getComponentId<T>();
                return dynamic_cast<S*>(this->systemMap[id].get());
            }

            template<typename T>
            const std::unordered_set<og::entity_t>& getSystemEntities() {
                return this->systemMap[og::getComponentId<T>()]->entities;
            }

            template<typename T>
            bool systemContains(const og::entity_t e) {                
                const auto& s = this->systemMap[og::getComponentId<T>()];
                return s->entities.find(e) != s->entities.end();                
            }

            void entityDestroy(const og::entity_t e) {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.erase(e);
                }
            }

            void update(const float dt) {
                for (const og::component_id_t id : this->systemOrder) {
                    this->systemMap[id]->update(dt);
                }                
            }

            void draw(sf::RenderWindow& window, const og::entity_t e) {
                for (const og::component_id_t id : this->entityToSystem[e]) {
                    this->systemMap[id]->draw(window, e);
                }
            }

            void clear() {
                for (auto& pair : this->systemMap) {
                    pair.second->entities.clear();
                }
            }

            std::size_t size() const {
                std::size_t s = 0;
                for (auto& pair : this->systemMap) {
                    s += pair.second->entities.size();
                }
                return s;
            }

    };
    
} // namespace og

