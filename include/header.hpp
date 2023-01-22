#ifndef HEADER_HPP
#define HEADER_HPP

#ifndef __APPLE__
#include <windows.h>
#endif

#include <iostream>
#include <map>
#include <math.h> 
#include "../include/dependencies/freeglut.h" 

using namespace std;

#define WIDTH 800
#define HEIGHT 600

#define TITLE_W 273
#define TITLE_H 44

#define TEXTURE_SIZE 16 * 1.5

#define WORLD_HEIGHT 255
#define FLAT_WORLD_DEPTH 5

#define OFFSET 15
#define HEIGHT_OFFSET 6

#define BUTTONS_POS_X (WIDTH / 2) - (invWidth / 2)
#define PLAYBUTTON_POS_Y (HEIGHT / 2) - (invHeight / 2)
#define EXITBUTTON_POS_Y (HEIGHT / 2) - (invHeight / 2) + (HEIGHT / 4)
#define BUTTON_TEXT_OFFSET_X (invWidth / 2) - (2 * OFFSET)

#define INV_POS_X (WIDTH / 2) - invWidth / 2
#define INV_POS_Y HEIGHT - invHeight - OFFSET
#define INV_SEL_SIZE 24 * 2

#define PI 3.1415

// угол поворота камеры
inline float angle = 0.0;
inline float speed_front = 3.0;
inline float speed_left = 3.0;

// координаты вектора направления движения камеры
inline float lx = speed_left, ly = 0.0f, lz = -speed_front;
// позиция камеры
inline float x = 0.0f, y = 0, z = 0.0f;
inline int rc_dist = 5;   // ray casting distance

//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
inline float yaw = 0.0f;
inline float pitch = 0.0f;
inline float deltaMove = 0;
inline float deltaMove_side = 0;
inline int delta_x = -1;
inline int delta_y = -1;

inline float rotate_block = 0;
inline const int fieldSize = 30;
inline float pos = 0.5;


// переменные для вычисления количества кадров в секунду
inline int frame;
inline long _time, timebase;
inline char fps[5];

// Size of inventory bar is 188x20	
inline int invWidth = 188 * 2;
inline int invHeight = 20 * 2;

inline GLuint texture[4];
inline GLuint ui[4];

struct block_t {
    bool exist;
    GLuint type;
};

inline struct block_t chunk[fieldSize][WORLD_HEIGHT][fieldSize];
inline int pointSize;

enum MENU {
    MAIN_MENU = 0,
    GAME,
    PAUSE
};

inline int gameState = MAIN_MENU;

enum TEXTURES {
    GRASS_SIDE = 0,
    GRASS_TOP,
    DIRT,
    BEDROCK
};

enum HUD_TEXTURES {
    INVENTORY = 0,
    INV_SELECTOR,
    MAIN_MENU_BG,
    TITLE,
    BUTTON
};

#endif