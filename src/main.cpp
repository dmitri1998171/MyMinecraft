#include "../include/header.hpp"
#include "../include/input.hpp"
#include "../include/UI.hpp"
#include "../include/HUD.hpp"
#include "../include/Button.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/dependencies/stb_image.h"
#define STB_PERLIN_IMPLEMENTATION
#include "../include/dependencies/stb_perlin.h"

map<string, Button*> buttons;

void buttonClickCheck(int x, int y) {
	for (map<string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
		if(it->second->isClicked(x, y)) {
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

void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

void makeABlock(int side_index, int top_index, int bottom_index) {
    float pos = 0.5;

   // Activate a texture.
   glBindTexture(GL_TEXTURE_2D, texture[side_index]);
    // Front
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, pos);
		glTexCoord2f(1, 1); glVertex3f( pos,  pos, pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos, pos);
	glEnd();

    // Back
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, -pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, -pos);
		glTexCoord2f(1, 1); glVertex3f( pos,  pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos, -pos);
	glEnd();

    // Left
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f(-pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos,  pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos,  pos, -pos);
	glEnd();

    // Right
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f(pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(pos,  pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(pos,  pos, -pos);
	glEnd();

   	glBindTexture(GL_TEXTURE_2D, texture[top_index]);

    // Top
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, pos, -pos);
	glEnd();

   	glBindTexture(GL_TEXTURE_2D, texture[bottom_index]);

    // Bottom
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, -pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, -pos, -pos);
	glEnd();
}

void drawFlatWorld(int fieldSize) {
	for (int i = -fieldSize / 2; i < fieldSize / 2; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = -fieldSize / 2; k < fieldSize / 2; k++) {
				glPushMatrix();
				glTranslatef(i, j, k);
				glRotatef(rotate_block, 0, 1, 0);

				if(j == 0)
					makeABlock(3, 3, 3);	// bedrock
				else if(j > 3)
					makeABlock(0, 1, 2);	// grass
				else
					makeABlock(2, 2, 2);	// dirt

				glPopMatrix();
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
 
	drawFlatWorld(fieldSize);
	drawHUD();

	if(gameState == PAUSE) 
		renderPause();
	else 
		computePos(deltaMove); // Отслеживаем перемещение камеры только когда играем

	glutSwapBuffers();
}

void stbLoadTexture(GLuint *tex, const char * filename, int req_channels) {
	/*
	req_channels:
		BMP-file = 0  
		JPEG-file = 4  
	*/
	int width = 0, height = 0, channels = 0;
		
	stbi_set_flip_vertically_on_load(true);  
	stbi_uc *image = stbi_load( filename, &width, &height, &channels, req_channels );

	if ( image != nullptr ) {
		glGenTextures(1, tex);
		glBindTexture(GL_TEXTURE_2D, *tex);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		stbi_image_free( image );
	}
	else {
		cout << "ERROR: Can't load " << filename << " texture!" << endl;
	}
}

void renderMenu() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	setOrthographicProjection(); 

	drawDebugLines();
		
	// drawTitle();
	drawTexture(&ui[TITLE], TITLE_W, TITLE_H, (WIDTH / 2) - (TITLE_W / 2), (HEIGHT / 4) - (TITLE_H / 2));
	buttons["play"]->draw(BUTTONS_POS_X, PLAYBUTTON_POS_Y);
	buttons["exit"]->draw(BUTTONS_POS_X, EXITBUTTON_POS_Y);

	drawBackground(&ui[MAIN_MENU_BG]);

	restorePerspectiveProjection(); 
	glutSwapBuffers();
}

void render() {
	switch (gameState) {
		case MAIN_MENU:
			renderMenu();
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
			buttons["continue"]->setVisible(false);
			buttons["main_menu"]->setVisible(false);
			buttons["play"]->setVisible(true);
			buttons["exit"]->setVisible(true);
			break;
		case GAME:
			renderScene();
			glutSetCursor(GLUT_CURSOR_NONE);				// Скрыть курсор
			break;
		case PAUSE:
			renderScene();
			buttons["continue"]->setVisible(true);
			buttons["main_menu"]->setVisible(true);
			buttons["play"]->setVisible(false);
			buttons["exit"]->setVisible(false);
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
			break;
	}
}

void createButtons() {
	buttons["play"] = new Button;
	buttons["play"]->setButtonColor(0, 255, 0);
	buttons["play"]->addText("PLAY", 255, 255, 255);
	
	buttons["exit"] = new Button;
	buttons["exit"]->setButtonColor(255, 0, 0);
	buttons["exit"]->addText("EXIT", 255, 255, 255);

	buttons["continue"] = new Button;
	buttons["continue"]->setButtonColor(0, 255, 0);
	buttons["continue"]->addText("Continue", 255, 255, 255);
	
	buttons["main_menu"] = new Button;
	buttons["main_menu"]->setButtonColor(255, 0, 0);
	buttons["main_menu"]->addText("Main Menu", 255, 255, 255);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	createButtons();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_TEXTURE_2D);		// Работа с текстурами
	glEnable (GL_DEPTH_TEST);		// тест глубины
	// glEnable(GL_CULL_FACE);			// occlusion query
	// glCullFace(GL_FRONT);
	// glEnable(GLUT_MULTISAMPLE);


	stbLoadTexture(&texture[GRASS_SIDE], "media/textures/grass_side.png", 4);
	stbLoadTexture(&texture[GRASS_TOP], "media/textures/grass_top.png", 4);
	stbLoadTexture(&texture[DIRT], "media/textures/dirt.png", 4);
	stbLoadTexture(&texture[BEDROCK], "media/textures/bedrock.png", 4);

	stbLoadTexture(&ui[INVENTORY], "media/textures/GUI/inventory.jpg", 4);
	stbLoadTexture(&ui[INV_SELECTOR], "media/textures/GUI/inventorySelector.png", 4);
	stbLoadTexture(&ui[MAIN_MENU_BG], "media/textures/GUI/mainMenuBackground.png", 4);
	stbLoadTexture(&ui[TITLE], "media/textures/GUI/minecraft.png", 4);
	
	// for (int i = 0; i < 5; i++)
	// 	for (int j = 0; j < 5; j++)
	// 		for (int k = 0; k < 5; k++)
	// 			cout << stb_perlin_noise3_seed(i, j, k, 0, 0, 0, 8) << endl;
	

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.

	glutDisplayFunc(render);
    glutReshapeFunc(changeSize);

	// glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);
    glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseSpecialKey);

	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
	glutMouseWheelFunc(mouseWheel);
 
	glutMainLoop();
 
	return 1;
}