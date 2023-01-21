#include "../../include/header.hpp"
#include "../../include/UI.hpp"
#include "../../include/world.hpp"
#include "../../include/draw.hpp"
#include "../../include/Button.hpp"

extern map<string, Button*> buttons;

void computePos(float deltaMove) {
	if(deltaMove) {
		x += deltaMove * lx * 0.1f;
		y += deltaMove * ly * 0.1f;
		z += deltaMove * lz * 0.1f;

		// update camera's direction
	}
	if(deltaMove_side) {
		x -= deltaMove_side * lz * 0.1f;
		z += deltaMove_side * lx * 0.1f;
	}

	lx = sin(angle + yaw);
	ly = -sin(angle + pitch);
	lz = -cos(angle + yaw);

	glutPostRedisplay();
}

void drawWorld() {
	for (int i = 0; i < fieldSize; i++) {
		for (int j = 0; j < WORLD_HEIGHT; j++) {
			for (int k = 0; k < fieldSize; k++) {
				if(chunk[i][j][k].exist == true) {
                    glPushMatrix();
                    glTranslatef(i, j, k);

                    if(chunk[i][j][k].type == BEDROCK)
					    makeABlock(3, 3, 3);	// bedrock
                    else if(chunk[i][j][k].type == GRASS_SIDE)
                        makeABlock(0, 1, 2);	// grass
                    else
                        makeABlock(2, 2, 2);	// dirt
				    
                    glPopMatrix();
                }
			}
		}
	}
}

void renderPause() {
	setOrthographicProjection(); 
	buttons["continue"]->draw(BUTTONS_POS_X, PLAYBUTTON_POS_Y);
	buttons["main_menu"]->draw(BUTTONS_POS_X, EXITBUTTON_POS_Y);
	restorePerspectiveProjection(); 
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(255, 255, 255);

    gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
 
    drawWorld();
	drawHUD();

	if(gameState == PAUSE) {
		renderPause();
    }
	else 
		computePos(deltaMove); // Отслеживаем перемещение камеры только когда играем

    glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void renderMenu() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	setOrthographicProjection(); 

	// drawDebugLines();
		
	// drawTexture(&ui[TITLE], TITLE_W, TITLE_H, (WIDTH / 2) - (TITLE_W / 2), (HEIGHT / 4) - (TITLE_H / 2));
	buttons["play"]->draw(BUTTONS_POS_X, PLAYBUTTON_POS_Y);
	buttons["exit"]->draw(BUTTONS_POS_X, EXITBUTTON_POS_Y);

// background image
	drawTexture(&ui[MAIN_MENU_BG], WIDTH, HEIGHT, 0, 0); 

	restorePerspectiveProjection(); 
	glutSwapBuffers();
}

void render() {
	switch (gameState) {
		case MAIN_MENU:
			buttons["continue"]->setVisible(false);
			buttons["main_menu"]->setVisible(false);
			buttons["play"]->setVisible(true);
			buttons["exit"]->setVisible(true);
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
			renderMenu();
			break;
		case GAME:
            buttons["continue"]->setVisible(false);
			buttons["main_menu"]->setVisible(false);
			buttons["play"]->setVisible(false);
			buttons["exit"]->setVisible(false);
			glutSetCursor(GLUT_CURSOR_NONE);				// Скрыть курсор
			renderScene();
			break;
		case PAUSE:
			buttons["continue"]->setVisible(true);
			buttons["main_menu"]->setVisible(true);
			buttons["play"]->setVisible(false);
			buttons["exit"]->setVisible(false);
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
			renderScene();
			break;
	}
}
