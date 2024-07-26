#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "scene_id.hpp"
#include "types.hpp"
#include "colors.hpp"


#define ASSETS_PATH "./assets/"
#define LOG_DIR "./log/"
#define ICON_IMAGE "./assets/icon.png"

namespace og {

    constexpr unsigned int SCREEN_WIDTH = 1280;
    constexpr unsigned int SCREEN_HEIGHT = 720;
    constexpr char WINDOW_TITLE[] = "Ougi";
    constexpr int FPS = 60;
    
    constexpr og::SceneId FIRST_SCENE = og::SceneId::TestScene2Id;
    constexpr bool DEBUD_MODE = true;

    constexpr og::zindex_t MIN_Z_INDEX = 0;
    constexpr og::zindex_t MAX_Z_INDEX = 10;

    constexpr float CAMERA_MAX_ZOOM = 4.0f;
    constexpr float CAMERA_MIN_ZOOM = 0.25f;
    constexpr float CAMERA_ZOOM_SPEED = 2.0f;

    constexpr og::entity_t MAX_ENTITIES = 4096;

    constexpr float SCREEN_CENTERX = SCREEN_WIDTH / 2.0f;
    constexpr float SCREEN_CENTERY = SCREEN_HEIGHT / 2.0f;
        
    const static sf::Vector2f VECTOR_ZERO(0.0f, 0.0f);

    const static sf::Color DEFAULT_BG_COLOR = og::colors::GREY;
    const static sf::Vector2f SCREEN_SIZE(SCREEN_WIDTH, SCREEN_HEIGHT);
    const static sf::Vector2f SCREEN_CENTER(SCREEN_CENTERX, SCREEN_CENTERY);
    const static sf::FloatRect SCREEN_RECT(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    constexpr float TILE_SIZE = 64.0f;

    
} // namespace og

