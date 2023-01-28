BIN := bin/main

SRC := $(wildcard src/impl/*.cpp) 
# REL_SRC := $(patsubst src/imp/%, %, $(SRC))

OBJECTS := $(SRC:.cpp=.o)
OBJECTS := $(patsubst src/impl/%, %, $(OBJECTS))
OBJECTS := $(addprefix obj/, $(OBJECTS))

CC := g++
CFLAGS := -Wno-deprecated-declarations --std=c++17

LIB := lib/libfreeglut.a
LIB_64 := lib/libfreeglut_x64.a
LIB_PATH := -L/System/Library/Frameworks -Llib

WIN_LDFLAGS := -lopengl32 -lglu32
LDFLAGS := -framework GLUT -framework OpenGL -framework Cocoa 

all: win64
	
win32: 
	$(CC) $(SRC) $(LIB) $(WIN_LDFLAGS) $(CFLAGS) 

obj/%.o: src/impl/%.cpp 
	$(CC) -c $< $(CFLAGS) -o $(patsubst src/impl/%, %, $@)

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o

win64: $(OBJECTS) obj/main.o
	$(CC) $(CFLAGS) $(OBJECTS) obj/main.o $(LIB_64) $(WIN_LDFLAGS) -o $(BIN).exe

clean:
	del obj\*.o

