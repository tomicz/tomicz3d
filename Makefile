CC = g++
CFLAGS = -Wall -std=c++17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -framework OpenGL `pkg-config --cflags --libs glew glfw3`
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = game_engine

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

