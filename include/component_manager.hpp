#pragma once
#include <cassert>
#include <memory>
#include "logger.hpp"
#include "components.hpp"
#include "component_array.hpp"
#include "component_id_manager.hpp"


namespace og {


    class ComponentManager {

        private:
            std::unordered_map<og::component_id_t, std::unique_ptr<og::IComponentArray>> componentMap{};
            og::ComponentArray<og::obstacle_t>* obstacleArray{};
            og::ComponentArray<og::transform_t>* transformArray{};
        
        private:
            template<typename T>
            void registerComponentArray() {
                this->componentMap.emplace(og::getComponentId<T>(), std::make_unique<og::ComponentArray<T>>());
            }

        public:
            ComponentManager() {
                this->componentMap.reserve(og::NUM_COMPONENTS);
                this->registerComponentArray<og::transform_t>();
                this->registerComponentArray<og::sprite_t>();
                this->registerComponentArray<og::obstacle_t>();
                if (this->componentMap.size() != og::NUM_COMPONENTS) {
                    og::Log::error("ComponentArrayMap size != NUM_COMPONENTS");
                }
                this->transformArray = dynamic_cast<og::ComponentArray<og::transform_t>*>(this->componentMap[og::getComponentId<og::transform_t>()].get());
                this->obstacleArray = dynamic_cast<og::ComponentArray<og::obstacle_t>*>(this->componentMap[og::getComponentId<og::obstacle_t>()].get());
            }

            og::transform_t& getTransform(const og::entity_t e) {
                return this->transformArray->at(e);
            }

            og::ComponentArray<og::obstacle_t>* getObstacleArray() {
                return this->obstacleArray;
            }
            
            template<typename T>
            void insert(const og::entity_t e, T c) {
                const og::component_id_t id = og::getComponentId<T>();
                dynamic_cast<og::ComponentArray<T>*>(this->componentMap[id].get())->insert(e, std::move(c));
            }

            template<typename T>
            void erase(const og::entity_t e) {
                const og::component_id_t id = og::getComponentId<T>();
                dynamic_cast<og::ComponentArray<T>*>(this->componentMap[id].get())->erase(e);
            }

            template<typename T>
            T& at(const og::entity_t e) {
                const og::component_id_t id = og::getComponentId<T>();
                return dynamic_cast<og::ComponentArray<T>*>(this->componentMap[id].get())->at(e);
            }

            void entityDestroy(const og::entity_t e) {
                for (auto& pair : this->componentMap) {
                    pair.second->erase(e);
                }
            }

            void clear() {
                for (auto& pair : this->componentMap) {
                    pair.second->clear();
                }
            }

            std::size_t size() const {
                std::size_t s = 0;
                for (auto& pair : this->componentMap) {
                    s += pair.second->size();
                }
                return s;
            }

    };
    
} // namespace og
