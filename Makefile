CC = g++
CFLAGS = -Wall -std=c++17 -I/opt/homebrew/include -Iinclude
LDFLAGS = -L/opt/homebrew/lib -framework OpenGL `pkg-config --cflags --libs glew glfw3`
SOURCES = src/main.cpp src/logger.cpp  # Add logger.cpp here
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE = build/game_engine

# Build everything, including the executable
all: $(EXECUTABLE)

# Create the build directory
build:
	mkdir -p build

# Linking the object files to create the executable
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking the executable..."
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files into object files
build/%.o: src/%.cpp | build
	@echo "Compiling $< into $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf build/*

