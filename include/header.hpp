#ifndef HEADER_HPP
#define HEADER_HPP

#ifndef __APPLE__
#include <windows.h>
#endif

#include <iostream>
#include <math.h> 
#include "../include/dependencies/freeglut.h" 
using namespace std;


#define WIDTH 800
#define HEIGHT 600

#define OFFSET 15
#define HEIGHT_OFFSET 6

// угол поворота камеры
inline float angle = 0.0;
inline float speed_front = 3.0;
inline float speed_left = 3.0;

// координаты вектора направления движения камеры
inline float lx = speed_left, ly = 0.0f, lz = -speed_front;
// позиция камеры
inline float x = 0.0f, y = 0, z = 0.0f;

//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
inline float yaw = 0.0f;
inline float pitch = 0.0f;
inline float deltaMove = 0;
inline float deltaMove_side = 0;
inline int delta_x = -1;
inline int delta_y = -1;

inline float rotate_block = 0;

// переменные для вычисления количества кадров в секунду
inline int frame;
inline long _time, timebase;
inline char fps[5];

// Size of inventory bar is 188x20	
inline int invWidth = 188 * 2;
inline int invHeight = 20 * 2;
inline int invSelector = 0;	// current selected object from inventory

inline GLuint texture[4];
inline GLuint hud[4];

inline int pointSize;

enum MENU {
    MAIN_MENU = 0,
    GAME,
    PAUSE
};

inline int gameState = MAIN_MENU;

#endif