CC = g++
CFLAGS = -Wall -std=c++17
LDFLAGS = -framework OpenGL `pkg-config --cflags --libs glfw3 glew`
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = game_engine

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJECTS) $(EXECUTABLE)
