CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Iinclude -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lglfw

SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/game_engine

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Ensure the build directory exists before compiling
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

# Example of a correctly indented command
build/main.o: src/main.cpp
	clang++ -std=c++17 -Wall -Iinclude -I/opt/homebrew/include -c src/main.cpp -o build/main.o
