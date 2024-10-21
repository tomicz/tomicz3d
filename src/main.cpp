#include "../include/logger.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

void handleWindowResize(int width, int height) {
    std::cout << "Window resized to " << width << "x" << height << std::endl;
}

int main() {
    Logger logger("../logs/engine.log");
    logger.log(Logger::INFO, "Game engine starting...");

    const double TARGET_FPS = 60.0;
    const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    bool running = true;
    int tick = 0;

    while (running) {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(currentFrameTime - lastFrameTime).count();

        if (deltaTime >= TARGET_FRAME_TIME) {
            lastFrameTime = currentFrameTime;

            std::cout << "\033[2J\033[1;1H";  // ANSI escape codes to clear console and move cursor to top-left

            std::cout << "Frame: " << tick << std::endl;

            logger.log(Logger::INFO, "Tick: " + std::to_string(tick));
            tick++;

            if (tick >= 600) {
                running = false;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    logger.log(Logger::INFO, "Game engine shutting down...");
    return 0;
}
