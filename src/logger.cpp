#include "../include/logger.hpp"

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app); // Open file in append mode
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::currentTime() {
    std::time_t t = std::time(nullptr);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return buffer;
}

void Logger::log(LogLevel level, const std::string& message) {
    std::string levelStr;

    switch (level) {
        case INFO:    levelStr = "INFO"; break;
        case WARNING: levelStr = "WARNING"; break;
        case ERROR:   levelStr = "ERROR"; break;
    }

    std::string logMessage = "[" + currentTime() + "] [" + levelStr + "] " + message;

    // Print to console
    std::cout << logMessage << std::endl;

    // Write to file
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;
    }
}
