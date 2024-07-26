#pragma once
#include <array>
#include <vector>


namespace og {


    unsigned long hash(const char* s);
    
    void sleepSeconds(int seconds);

    void sleepMili(unsigned long mili);

    int randint(int start, int end);

    template<typename T, std::size_t size>
    T& choiceArray(const std::array<T, size>& arr) {
        return arr[og::randint(0, arr.size() - 1)];
    }

    template<typename T>
    T& choiceVec(const std::vector<T>& arr) {
        return arr[og::randint(0, arr.size() - 1)];
    }
    

} // namespace og
