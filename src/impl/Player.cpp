#include "../../include/Player.hpp"


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

