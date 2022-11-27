#include "../include/header.hpp"
#include "../include/input.hpp"


void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}

	glutPostRedisplay();
} 
 
void releaseKey(int key, int x, int y) { 	
	switch (key) {
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
} 

void mouseMove(int x, int y) { 	
	// Перевод от коорд. курсора 0,0 к коорд. w/2, h/2
	// Чтобы камера вращалась не только влево и вниз (увелич. коорд. относ. 0,0)
	delta_x = (WIDTH / 2) - x;
	delta_y = (HEIGHT / 2) - y;

	yaw = -delta_x * 0.001f;
	pitch = -delta_y * 0.001f;

	// update camera's direction
	lx = sin(angle + yaw);
	ly = -sin(angle + pitch);
	lz = -cos(angle + yaw);

	glutPostRedisplay();
}
 
void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
 
		// when the button is released
		if (state == GLUT_UP) {

		}
		else  {// state = GLUT_DOWN

		}
	}
}
