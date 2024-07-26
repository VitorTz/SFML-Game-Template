#pragma once
#include <filesystem>
#include <mutex>


namespace og {


    enum LogLevel {
        INFO,
        WARNING,
        ERROR
    };


    class Log {

        private:
            static std::mutex mutex;
            static std::filesystem::path logFile;

        public:
            static void init();
            static void log(
                const std::string& message, 
                LogLevel level                
            );
            static void info(const std::string& message);
            static void warning(const std::string& message);
            static void error(const std::string& message);
    };
    
    
} // namespace og

