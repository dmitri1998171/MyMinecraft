#include "../../include/header.hpp"
#include "../../include/input.hpp"
#include "../../include/Button.hpp"

extern map<string, Button*> buttons;

void pressKey(unsigned char key, int x, int y) {
    switch (key) {
// Escape
        case 27:
			if(gameState != MAIN_MENU) {
				if(gameState == GAME) gameState = PAUSE; 
				else gameState = GAME;
			}
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

	glutPostRedisplay();
}

void buttonClickCheck(int x, int y) {
	for (map<string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
		if(it->second->isClicked(x, y) && it->second->isVisible()) {
			cout << it->first << " button was clicked!" << endl;

			if(it->first == "play") 
				gameState = GAME;

			if(it->first == "exit")
				exit(0);

			if(it->first == "continue") 
				gameState = GAME;

			if(it->first == "main_menu") 
				gameState = MAIN_MENU;
		}
	}
}

// checking the distance for correctness
bool check(int x, int y, int z) {
   if ((x < 0) || (x >= 1000) || 
	   (y < 0) || (y >= 1000) || 
	   (z < 0) || (z >= 1000)) return false;
  
   return 1;
}

void rayCast(int button) {
	// cout << "rayCast\n";

	float loc_x = x;
	float loc_y = y;
	float loc_z = z;

	loc_x += lx * 0.1f;
	loc_y += ly * 0.1f;
	loc_z += lz * 0.1f;

	int X, Y, Z, oldX, oldY, oldZ;
	int curr_dist = 1;			// ray cast distance 

	while(curr_dist < rc_dist) {
		loc_x += sin(angle + yaw);   
		loc_y += -sin(angle + pitch);   
		loc_z += -cos(angle + yaw);   

		X = loc_x;
		Y = loc_y;
		Z = loc_z;
		
		// if(loc_z < 10) {
		// 	if((loc_z / 10) < Z)
		// 		Z = loc_z + 0.4; 
		// 	else
		// 		Z = loc_z - 0.4; 
		// }

		if (check(X, Y, Z)) {				// if coords are valid 
			cout << endl;
			cout << "x: " << loc_x << " y: " << loc_y << " z: " << loc_z << endl;
			cout << "curr_dist: " << curr_dist << endl;

			cout << "X: " << X << " Y: " << Y << " Z: " << Z << endl;
			// cout << "lx: " << lx << " ly: " << ly << " lz: " << lz << endl;

			if (button == GLUT_LEFT_BUTTON) { 					// and if LMB was clicked
				chunk[X][Y][Z] = 0; 			// drop the block
				cout << "drop the block" << endl;
				break;						// break the loop for optimization
			}
			if(button == GLUT_RIGHT_BUTTON) {							// if RMB was clicked 
				cout << "create the block" << endl;
				chunk[oldX][oldY][oldZ] = 1; // put a new block
				break;						// break the loop for optimization
			}
		}
		
		oldX = X; 
		oldY = Y; 
		oldZ = Z;

		curr_dist++;
	}
}

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			if(gameState == PAUSE || gameState == MAIN_MENU)
				buttonClickCheck(x, y);
			
			if(gameState == GAME)
				rayCast(button);
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
