CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Iinclude
LDFLAGS := -L/opt/homebrew/lib -lglfw

SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/game_engine

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
