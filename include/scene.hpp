#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "types.hpp"
#include "scene_id.hpp"


namespace og {    


    class Scene {

        public:
            virtual ~Scene() = default;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window) = 0;
            virtual void unload() = 0;

    };    
    

    class LoadingScreen : public og::Scene {

        public:
            LoadingScreen();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;
            void unload() override;

    };

    class TitleScreenScene : public og::Scene {

        public:
            TitleScreenScene();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;
            void unload() override;

    };


    class LevelScene : public og::Scene {

        public:
            LevelScene();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;
            void unload() override;

    };

    class SceneManager {

        private:
            static std::unique_ptr<og::Scene> scene;
            static std::unique_ptr<og::LoadingScreen> loadingScreen;
            static og::SceneId sceneId;
            static bool shouldChangeScene;
            static bool isChangingScene;
        
        private:
            static void loadNextScene();
            static void changeScene();

        public:
            static void init();
            static void requestSceneChange(og::SceneId sceneId);
            static void update(float dt);
            static void draw(sf::RenderWindow& window);

    };


    class TestScene1 : public og::Scene {

        private:
            std::unordered_map<og::entity_t, float> entitySpeed{};

        public:
            TestScene1();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;
            void unload() override;

    };

    class TestScene2 : public og::Scene {

        private:            
            og::entity_t playerEntity;
            og::entity_t enemyEntity;

        public:
            TestScene2();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;
            void unload() override;

    };

} // namespace og
