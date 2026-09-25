CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra $(shell pkg-config --cflags opencv4)
LDLIBS   := $(shell pkg-config --libs opencv4)

SRC := src/main.cpp src/cli.cpp src/image.cpp src/render.cpp src/ansi.cpp src/html.cpp
OBJ := src/main.o src/cli.o src/image.o src/render.o src/ansi.o src/html.o

termart: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o termart $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: termart
	./termart examples/building.jpg --width 80

clean:
	rm -f $(OBJ) termart

.PHONY: run clean
