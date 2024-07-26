#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include "entity_manager.hpp"
#include "component_manager.hpp"
#include "system_manager.hpp"


namespace og {


    class ECS {

        private:
            og::EntityManager entity{};
            og::ComponentManager component{};
            og::SystemManager system{};
        
        private:
            std::queue<og::entity_t> entitiesToDestroy;
            bool shouldDestroyAllEntities = false;
        
        private:
            std::map<og::zindex_t, std::vector<std::pair<float, og::entity_t>>> camera{};
            bool isOnCamera[og::MAX_ENTITIES];
        
        private:
            void submitToCamera(const og::entity_t e, const og::zindex_t zindex) {
                if (this->isOnCamera[e] == false) {
                    this->isOnCamera[e] = true;
                    this->camera[zindex].push_back(std::make_pair(0.0f, e));
                }
            }

            void rmvFromCamera(const og::entity_t e) {
                if (this->isOnCamera[e] == true) {
                    this->isOnCamera[e] = false;
                    const og::zindex_t zindex = this->component.at<og::transform_t>(e).zindex;
                    std::vector<std::pair<float, og::entity_t>>& v = this->camera[zindex];
                    for (std::size_t i = 0; i < v.size(); i++) {
                        if (v[i].second == e) {
                            v.erase(v.begin() + i);
                            return;
                        }
                    }
                }
            }
        
        public:
            
            void init() {
                for (og::zindex_t zindex = 0; zindex <= og::MAX_Z_INDEX; zindex++) {
                    this->camera.insert({zindex, {}});
                }
                for (auto& pair : this->camera) {
                    pair.second.reserve(og::MAX_ENTITIES);
                }
                for (og::entity_t i = 0; i < og::MAX_ENTITIES; i++) {
                    this->isOnCamera[i] = false;
                }
            }
            
            og::entity_t entityCreate(const og::zindex_t zindex, const bool onCamera) {
                const og::entity_t e = this->entity.entityCreate();
                this->component.insert<og::transform_t>(e, og::transform_t{.zindex = zindex});
                if (onCamera) {
                    this->submitToCamera(e, zindex);
                }
                return e;
            }

            void entityDestroy(const og::entity_t e) {
                this->entitiesToDestroy.push(e);
            }

            template<typename T>
            void addComponent(const og::entity_t e, T c) {
                this->component.insert<T>(e, std::move(c));
                this->system.insert<T>(e);
            }

            template<typename T>
            void rmvComponent(const og::entity_t e) {
                this->component.erase<T>(e);
                this->system.erase<T>(e);
            }

            template<typename T>
            T& getComponent(const og::entity_t e) {
                return this->component.at<T>(e);
            }

            template<typename T>
            void addToSystem(const og::entity_t e) {
                this->system.insert<T>(e);
            }

            template<typename T>
            void rmvFromSystem(const og::entity_t e) {
                this->system.erase<T>(e);
            }

            template<typename T, typename S>
            S* getSystem() {
                return this->system.getSystem<T, S>();
            }

            template<typename T>
            bool systemContains(const og::entity_t e) {
                return this->system.systemContains<T>(e);
            }

            void update(const float dt) {
                this->system.update(dt);

                if (this->shouldDestroyAllEntities) {
                    this->shouldDestroyAllEntities = false;
                    for (auto& pair : this->camera) {
                        pair.second.clear();
                    }
                    for (og::entity_t i = 0; i < og::MAX_ENTITIES; i++) {
                        this->isOnCamera[i] = false;
                    }
                    this->entitiesToDestroy = std::queue<og::entity_t>();
                    this->entity.clear();
                    this->component.clear();
                    this->system.clear();
                }

                while (!this->entitiesToDestroy.empty()) {
                    const og::entity_t e = this->entitiesToDestroy.front();
                    this->entitiesToDestroy.pop();
                    this->rmvFromCamera(e);
                    this->entity.entityDestroy(e);
                    this->component.entityDestroy(e);
                    this->system.entityDestroy(e);
                }
            }

            void draw(sf::RenderWindow& window) {
                // zindex and y sort camera
                for (auto& pair : this->camera) {
                    for (auto& pair2 : pair.second) {
                        const og::transform_t& t = this->component.at<og::transform_t>(pair2.second);
                        pair2.first = t.pos.y + t.size.y / 2.0f;
                    }
                    std::sort(pair.second.begin(), pair.second.end());
                    for (auto& pair2 : pair.second) {                        
                        this->system.draw(window, pair2.second);
                    }
                }                
            }

            std::size_t numEntities() const {
                return this->entity.size();
            }

            std::size_t numComponents() const {
                return this->component.size();
            }

            std::size_t numSystem() const {
                return this->system.size();
            }

    };

    inline og::ECS gEcs{};
    
} // namespace og
