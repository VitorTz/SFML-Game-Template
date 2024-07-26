#pragma once
#include <SFML/Graphics.hpp>
#include <memory>


namespace og {

    enum SceneId {
        TitleScreenSceneId,
        LevelSceneId
    };


    class Scene {

        public:
            virtual ~Scene() = default;
            virtual void update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window) = 0;

    };
    

    class LoadingScreen : public og::Scene {

        public:
            LoadingScreen();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };

    class TitleScreenScene : public og::Scene {

        public:
            TitleScreenScene();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };


    class LevelScene : public og::Scene {

        public:
            LevelScene();
            void update(float dt) override;
            void draw(sf::RenderWindow& window) override;

    };

    class SceneManager {

        private:
            static std::unique_ptr<og::Scene> scene;
            static std::unique_ptr<og::LoadingScreen> loadingScreen;
            static og::SceneId sceneId;
            static bool shouldChangeScene;
            static bool isChangingScene;
        
        private:
            static void changeScene();

        public:
            static void init();
            static void requestSceneChange(og::SceneId sceneId);
            static void update(float dt);
            static void draw(sf::RenderWindow& window);

    };

} // namespace og
