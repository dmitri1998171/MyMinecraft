BIN := bin/main
SRC := src/main.cpp src/input.cpp
CC := g++
LIB_PATH := -L/System/Library/Frameworks -Llib
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa 
CFLAGS := -Wno-deprecated-declarations --std=c++17

all:
	clear && $(CC) $(SRC) $(LIB_PATH) $(LDFLAGS) $(CFLAGS) -o $(BIN)
	
clean:
	rm -rf $(BIN)