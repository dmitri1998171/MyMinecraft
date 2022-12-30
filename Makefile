BIN := bin/main
SRC := src/main.cpp src/input.cpp src/UI.cpp src/Button.cpp src/HUD.cpp
CC := g++
CFLAGS := -Wno-deprecated-declarations --std=c++17

LIB := lib/libfreeglut.a
LIB_64 := lib/libfreeglut_x64.a
LIB_PATH := -L/System/Library/Frameworks -Llib

WIN_LDFLAGS := -lopengl32 -lglu32
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa 

all:
	clear && $(CC) $(SRC) $(LIB_PATH) $(LDFLAGS) $(CFLAGS) -o $(BIN)
	
win32:
	$(CC) $(SRC) $(LIB) $(WIN_LDFLAGS) $(CFLAGS) -o $(BIN).exe

win64:
	$(CC) $(SRC) $(LIB_64) $(WIN_LDFLAGS) $(CFLAGS) -o $(BIN).exe

clean:
	rm -rf $(BIN)