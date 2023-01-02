#include "../../include/header.hpp"
#include "../../include/input.hpp"
#include "../../include/Button.hpp"

void pressKey(unsigned char key, int x, int y) {
    switch (key) {
// Escape
        case 27:
			gameState == GAME ? gameState = PAUSE : gameState = GAME;
            break;
        
// Inventory selector
		case 49: invSelector = 0; break;
		case 50: invSelector = 1; break;
		case 51: invSelector = 2; break;
		case 52: invSelector = 3; break;
		case 53: invSelector = 4; break;
		case 54: invSelector = 5; break;
		case 55: invSelector = 6; break;
		case 56: invSelector = 7; break;
		case 57: invSelector = 8; break;

// Moving
        case 119:       // W
            deltaMove = 0.5f; break;
        case 115:       // S
           deltaMove = -0.5f; break;
        case 97:        // A
            deltaMove_side = -0.5f; break;
        case 100:       // D
            deltaMove_side = 0.5f; break;
    }

	glutPostRedisplay();
}

void pressSpecialKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_UP:   deltaMove =  0.5f; break;
		case GLUT_KEY_DOWN: deltaMove = -0.5f; break;

		case GLUT_KEY_LEFT:  deltaMove_side = -0.5f; break;
        case GLUT_KEY_RIGHT: deltaMove_side = 0.5f; break;
	}

	glutPostRedisplay();
} 

void releaseSpecialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0; break;

        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaMove_side = 0; break;
	}
} 

void releaseKey(unsigned char key, int x, int y) {
	switch (key) {
        case 119:
        case 115: deltaMove = 0; break;

        case 97:
        case 100: deltaMove_side = 0; break;
	}
} 

void mouseMove(int x, int y) { 	
	// Перевод от коорд. курсора 0,0 к коорд. w/2, h/2
	// Чтобы камера вращалась не только влево и вниз (увелич. коорд. относ. 0,0)
	delta_x = (WIDTH / 2) - x;
	delta_y = (HEIGHT / 2) - y;

	yaw = -delta_x * 0.01f;
	pitch = -delta_y * 0.01f;

	// update camera's direction
	lx = sin(angle + yaw);
	ly = -sin(angle + pitch);
	lz = -cos(angle + yaw);

	glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			// cout << "Left mouse button click" << endl;
			buttonClickCheck(x, y);
		}
		else  {// state = GLUT_DOWN
		}
	}
}

void mouseWheel(int wheel, int direction, int x, int y) {
	if(direction > 0) 
		invSelector++;
	else 
		invSelector--;
	
	if(invSelector > 8)
		invSelector = 0;

	if(invSelector < 0)
		invSelector = 8;

   glutPostRedisplay();
}  
