CC = g++
CFLAGS = -Wall -std=c++17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -framework OpenGL `pkg-config --cflags --libs glew glfw3`
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE = build/game_engine

# Create build directory if it doesn't exist
build:
	mkdir -p build

all: build $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

build/%.o: src/%.cpp | build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*

