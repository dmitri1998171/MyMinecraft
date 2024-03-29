#include "../../include/header.hpp"
#include "../../include/input.hpp"
#include "../../include/Button.hpp"
#include "../../include/UI.hpp"
#include "../../include/Inventory.hpp"
#include "../../include/Player.hpp"

extern map<string, Button*> buttons;
extern Inventory inventory;
extern Player player;

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
		case 49: inventory.setSelect(0); break;
		case 50: inventory.setSelect(1); break;
		case 51: inventory.setSelect(2); break;
		case 52: inventory.setSelect(3); break;
		case 53: inventory.setSelect(4); break;
		case 54: inventory.setSelect(5); break;
		case 55: inventory.setSelect(6); break;
		case 56: inventory.setSelect(7); break;
		case 57: inventory.setSelect(8); break;

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
	if(gameState == GAME) {
		// Перевод от коорд. курсора 0,0 к коорд. w/2, h/2
		// Чтобы камера вращалась не только влево и вниз (увелич. коорд. относ. 0,0)
		delta_x += ((WIDTH / 2) - x);
		delta_y += ((HEIGHT / 2) - y);

		yaw = -delta_x * 0.01f;
		pitch = -delta_y * 0.01f;

		glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.
	}

	if(gameState == PAUSE || gameState == MAIN_MENU) {
		for (map<string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
				if(it->second->isHovered(x, y)) 
					it->second->setHover(true);

				else
					it->second->setHover(false);
		}

	}
	
	glutPostRedisplay();
}

void buttonClickCheck(int button, int state, int x, int y) {	
	if(state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			for (map<string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
				if(it->second->isHovered(x, y)) {
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
	}
}

// checking the distance for correctness
bool distCheck(int x, int y, int z) {
   if ((x < 0) || (x >= fieldSize) || 
	   (y < 0) || (y >= fieldSize) || 
	   (z < 0) || (z >= fieldSize)) return false;
  
   return 1;
}

void rayCast(int button, int state) {
	int X, Y, Z, oldX, oldY, oldZ;
	int curr_dist = 1;									// ray casting distance 

	float loc_x = player.getX() + lx;
	float loc_y = player.getY() + ly;
	float loc_z = player.getZ() + lz;

	while(curr_dist < rc_dist) {
		loc_x += sin(yaw);
		loc_y += -sin(pitch);
		loc_z += -cos(yaw);

		X = loc_x + pos;
		Y = loc_y + pos;
		Z = loc_z + pos;

		// if (distCheck(X, Y, Z)) {						// if coords are valid 
		// 	if(chunk[X][Y][Z].exist == true) {
		// 		if(state == GLUT_UP) {
		// 			if (button == GLUT_LEFT_BUTTON) { 	// and if LMB was clicked
		// 				chunk[X][Y][Z].exist = false; 	// drop the block
		// 				inventory.addToInventory(X, Y, Z);
		// 				break;							// break the loop for optimization
		// 			}

		// 			if(button == GLUT_RIGHT_BUTTON) {	// if RMB was clicked 
		// 				int block = inventory.deleteFromInventory();

		// 				if(block != -1) {
		// 					chunk[oldX][oldY][oldZ].exist = block; // put a new block
		// 					chunk[oldX][oldY][oldZ].type = inventory.getSelect(); // put a new block
		// 				}
						
		// 				break;							// break the loop for optimization
		// 			}
		// 		}
		// 	}
		// }

		oldX = X; 
		oldY = Y; 
		oldZ = Z;

		curr_dist++;
	}
}

void mouseButton(int button, int state, int x, int y) {
	if(gameState == PAUSE || gameState == MAIN_MENU)
		buttonClickCheck(button, state, x, y);
	
	if(gameState == GAME)
		player.rayCast(button, state);
}

void mouseWheel(int wheel, int direction, int x, int y) {
	inventory.changeSelect(direction);
	glutPostRedisplay();
}  
