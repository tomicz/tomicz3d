# Compiler and flags
CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Iinclude -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL

# Directories
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/game_engine

# Sources and object files (including subdirectories)
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(SRC_DIR)/main.cpp
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Ensure the build directory exists before compiling
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Check the sources and object files
$(info Sources: $(SRCS))
$(info Object Files: $(OBJS))

# Target for building the executable
$(TARGET): $(OBJS)
	@echo "Linking the executable..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Executable $(TARGET) has been created."

# Rule for building object files from source
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove build directory
clean:
	rm -rf $(BUILD_DIR)
	@echo "Build directory removed."

.PHONY: clean

