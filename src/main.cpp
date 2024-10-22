#include <iostream>
#include <chrono>
#include <iomanip>

class Game {
public:
    void Initialize() {
        std::cout << "Game started." << std::endl;
    }

    void try_recursion(){
        std::cout << "recusrion" << std::endl;
        try_recursion();
    }

    void ProcessInput() {
        // Process input here
    }

    void Update() {
        // Update game state here
    }

    void Render() {
        // Render frame here
    }

    void Run() {
        Initialize();
        
        int frameCount = 0;
        auto lastFpsUpdate = std::chrono::high_resolution_clock::now();

        while (isRunning) {
            ProcessInput();
            Update();
            Render();

            frameCount++;

            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastFpsUpdate);
            try_recursion();
            
            if (elapsed.count() >= 1) {
                double fps = frameCount / elapsed.count();
                std::cout << "\rFPS: " << std::fixed << std::setprecision(2) << fps << std::flush;
                
                frameCount = 0;
                lastFpsUpdate = now;
            }
        }

        std::cout << "\nExiting game loop..." << std::endl;
    }

private:
    bool isRunning = true;
};

int main() {
    Game game;
    std::cout << "Starting game..." << std::endl;
    game.Run();
    std::cout << "Game ended." << std::endl;
    return 0;
}
