#include "../include/logger.hpp"
#include "../include/constants.hpp"
#include "../include/exit.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>


std::mutex og::Log::mutex;
std::filesystem::path og::Log::logFile;


void og::Log::init() {
    std::filesystem::create_directory(LOG_DIR);

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_time);
    
    std::ostringstream str;
    
    str << LOG_DIR << std::put_time(now_tm, "%Y/%m/%d/%H:%M:%S.log");
    og::Log::logFile = std::filesystem::path(str.str());    
    std::filesystem::create_directories(og::Log::logFile.parent_path());    
}


void og::Log::log(
    const std::string& msg, 
    const og::LogLevel level    
) {
    std::string label;
    switch (level) {
        case LogLevel::INFO:
            label = "INFO";
            break;
        case LogLevel::WARNING:
            label = "WARNING";
            break;
        case LogLevel::ERROR:
            label = "ERROR";
            break;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_time);

    og::Log::mutex.lock();    
        std::ofstream logFile(og::Log::logFile, std::ios_base::app);
        if (logFile.is_open()) {
            logFile << std::put_time(now_tm, "[%H:%M:%S] ") << label << ": " << msg << '\n';
            logFile.close();
        }
    og::Log::mutex.unlock();

    std::cout << "===> " << '[' << label << ": " << msg << ']' << '\n';
    if (level == og::ERROR) {
        og::requestGameToExit();
    }
}


void og::Log::info(const std::string& message) {
    og::Log::log(message, og::LogLevel::INFO);
}


void og::Log::warning(const std::string& message) {
    og::Log::log(message, og::LogLevel::WARNING);
}

void og::Log::error(const std::string& message) {
    og::Log::log(message, og::LogLevel::ERROR);
}