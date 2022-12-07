#ifndef INPUT_HPP
#define INPUT_HPP

void pressKey(unsigned char key, int x, int y);
void pressSpecialKey(int key, int xx, int yy);
void releaseKey(int key, int x, int y);
void mouseMove(int x, int y);
void mouseButton(int button, int state, int x, int y);
// void mouseWheel(int wheel, int direction, int x, int y);

#endif