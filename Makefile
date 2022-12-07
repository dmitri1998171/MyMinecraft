BIN := bin/main
SRC := src/main.cpp src/input.cpp src/UI.cpp
CC := g++
LIB := lib/*
LIB_PATH := -L/System/Library/Frameworks -Llib
WIN_LDFLAGS :=  -lopengl32 -lglu32
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa 
CFLAGS := -Wno-deprecated-declarations --std=c++17

all:
	clear && $(CC) $(SRC) $(LIB_PATH) $(LDFLAGS) $(CFLAGS) -o $(BIN)
	
win32:
	$(CC) $(SRC) $(LIB) $(WIN_LDFLAGS) $(CFLAGS) -o $(BIN).exe

clean:
	rm -rf $(BIN)