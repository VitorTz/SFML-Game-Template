#include "../include/util.hpp"
#include <random>
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
    std::uniform_int_distribution<std::mt19937::result_type> d(1, 6);
    return d(rng);
}


void og::sleepSeconds(const int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}


void og::sleepMili(const unsigned long mili) {
    std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}