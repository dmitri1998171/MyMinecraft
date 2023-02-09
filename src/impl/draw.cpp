#include "../../include/header.hpp"
#include "../../include/UI.hpp"
#include "../../include/draw.hpp"
#include "../../include/Button.hpp"
#include "../../include/Player.hpp"
#include "../../include/Map.hpp"

extern map<string, Button*> buttons;
extern Player player;
extern Map _map;

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

	player.update();
	_map.checkCurrentPosition(player.getX(), player.getZ());

	_map.makeABlock(skybox[SIDE], skybox[TOP], skybox[BOTTOM], 550);	// skybox
    _map.draw();
	drawHUD();

	if(gameState == PAUSE) {
		renderPause();
	}
	else {
		player.move();
    	player.lookAround();
	}

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
			
			// glEnable(GL_CULL_FACE);			// occlusion query
			// glCullFace(GL_BACK);
			glutSetCursor(GLUT_CURSOR_NONE);				// Скрыть курсор
	
			renderScene();
			break;
		case PAUSE:
			buttons["continue"]->setVisible(true);
			buttons["main_menu"]->setVisible(true);
			buttons["play"]->setVisible(false);
			buttons["exit"]->setVisible(false);

			// glDisable(GL_CULL_FACE);			// occlusion query
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор

			renderScene();
			break;
	}
}
