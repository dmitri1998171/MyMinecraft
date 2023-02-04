#include "../../include/Player.hpp"
#include "../../include/Inventory.hpp"

extern Inventory inventory;

// checking the distance for correctness
bool distCheck(int x, int y, int z) {
   if ((x < 0) || (x >= fieldSize) || 
	   (y < 0) || (y >= fieldSize) || 
	   (z < 0) || (z >= fieldSize)) return false;
  
   return 1;
}

Player::Player() {
    x = 0, y = 0, z = 0;
    dx = 0, dy = 0, dz = 0;
    height = 3;
    speed = 3;
}

void Player::update() {
    move();
    lookAround();

    gluLookAt(x, y + height, z,
		  x + lx, y + height + ly, z + lz,
		  0.0f, 1.0f, 0.0f);

    // collision();

    dx = dz = 0;
}

void Player::move() {
    if(deltaMove) {
		x += deltaMove * lx * 0.1f;
		y += deltaMove * ly * 0.1f;
		z += deltaMove * lz * 0.1f;
	}

	if(deltaMove_side) {
		x -= deltaMove_side * lz * 0.1f;
		z += deltaMove_side * lx * 0.1f;
	}
}

void Player::lookAround() {
	lx = sin(yaw);
	ly = -sin(pitch);
	lz = -cos(yaw);

	glutPostRedisplay();
}

void Player::rayCast(int button, int state) {
	int X, Y, Z, oldX, oldY, oldZ;
	int curr_dist = 1;									// ray casting distance 

	float loc_x = x + lx;
	float loc_y = y + height + ly;
	float loc_z = z + lz;

	while(curr_dist < rc_dist) {
		loc_x += sin(yaw);
		loc_y += -sin(pitch);
		loc_z += -cos(yaw);

		X = loc_x + pos;
		Y = loc_y + pos;
		Z = loc_z + pos;

		if (distCheck(X, Y, Z)) {						// if coords are valid 
			if(chunk[X][Y][Z].exist == true) {
				if(state == GLUT_UP) {
					if (button == GLUT_LEFT_BUTTON) { 	// and if LMB was clicked
						chunk[X][Y][Z].exist = false; 	// drop the block
						inventory.addToInventory(X, Y, Z);
						break;							// break the loop for optimization
					}

					if(button == GLUT_RIGHT_BUTTON) {	// if RMB was clicked 
						int block = inventory.deleteFromInventory();

						if(block != -1) {
							chunk[oldX][oldY][oldZ].exist = block; // put a new block
							chunk[oldX][oldY][oldZ].type = inventory.getSelect(); // put a new block
						}
						
						break;							// break the loop for optimization
					}
				}
			}
		}

		oldX = X; 
		oldY = Y; 
		oldZ = Z;

		curr_dist++;
	}
}

void Player::collision() {

}

float Player::getX() {
    return x;    
}

float Player::getY() {
    return y;
}

float Player::getZ() {
    return z;  
}


Player player;