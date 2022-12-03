#ifndef HEADER_HPP
#define HEADER_HPP

#include <GLUT/glut.h> 
#include <math.h> 
#include <iostream>
using namespace std;


#define WIDTH 800
#define HEIGHT 600

// угол поворота камеры
inline float angle = 0.0;
inline float speed_front = 3.0;
inline float speed_left = 3.0;

// координаты вектора направления движения камеры
inline float lx = speed_left, ly = 0.0f, lz = -speed_front;
// XZ позиция камеры
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

#endif