#include "../include/exit.hpp"
#include "../include/globals.hpp"
#include "../include/texture_pool.hpp"
#include "../include/font.hpp"


void og::exitGame() {
    og::TexturePool::clear();
    og::FontPool::clear();
}


void og::requestGameToExit() {
    og::globals::gameIsRunning = false;    
}