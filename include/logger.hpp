#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger {
public:
    enum LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    Logger(const std::string& filename);
    ~Logger();

    void log(LogLevel level, const std::string& message);

private:
    std::ofstream logFile;
    std::string currentTime();
};

