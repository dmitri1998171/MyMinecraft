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

void clickCheck(int x, int y) {
	for (map<string, Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
		if(it->second->isClicked(x, y))
			cout << it->first << " was clicked!" << endl;
	}
}

void computePos(float deltaMove) {
	if(deltaMove) {
		x += deltaMove * lx * 0.1f;
		y += deltaMove * ly * 0.1f;
		z += deltaMove * lz * 0.1f;
	}
	if(deltaMove_side) {
		x -= deltaMove_side * lz * 0.1f;
		z += deltaMove_side * lx * 0.1f;
	}

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

void renderScene(void) {
	computePos(deltaMove);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
 
	int fieldSize = 30;
	drawFlatWorld(fieldSize);

	drawHUD();

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

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		stbi_image_free( image );
	}
	else {
		cout << "ERROR: Can't load a texture!" << endl;
	}
}

void renderMenu() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	setOrthographicProjection(); 

	// drawDebugLines();
		
	
	buttons["play"]->setButtonColor(0, 255, 0);
	buttons["play"]->addText("PLAY", 255, 255, 255);
	buttons["play"]->draw(BUTTONS_POS_X, PLAYBUTTON_POS_Y);
	
	buttons["exit"]->setButtonColor(255, 0, 0);
	buttons["exit"]->addText("EXIT", 255, 255, 255);
	buttons["exit"]->draw(BUTTONS_POS_X, EXITBUTTON_POS_Y);

	drawBackground();

	restorePerspectiveProjection(); 
	glutSwapBuffers();
}

void render() {
	switch (gameState) {
	case MAIN_MENU:
		renderMenu();
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
		break;
	case GAME:
		renderScene();
		glutSetCursor(GLUT_CURSOR_NONE);				// Скрыть курсор
		break;
	case PAUSE:
		// renderMenu();
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);			// Показать курсор
		break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	buttons["play"] = new Button;
	buttons["exit"] = new Button;

	glEnable (GL_TEXTURE_2D);		// Работа с текстурами
	glEnable (GL_DEPTH_TEST);		// тест глубины
	// glEnable(GL_CULL_FACE);			// occlusion query
	// glCullFace(GL_FRONT);
	// glEnable(GLUT_MULTISAMPLE);

	stbLoadTexture(&texture[0], "media/textures/grass_side.png", 4);
	stbLoadTexture(&texture[1], "media/textures/grass_top.png", 4);
	stbLoadTexture(&texture[2], "media/textures/dirt.png", 4);
	stbLoadTexture(&texture[3], "media/textures/bedrock.png", 4);

	stbLoadTexture(&hud[0], "media/textures/GUI/inventory.jpg", 4);
	stbLoadTexture(&hud[1], "media/textures/GUI/inventorySelector.png", 4);
	stbLoadTexture(&hud[2], "media/textures/GUI/crosshair.png", 4);

	// for (int i = 0; i < 5; i++)
	// 	for (int j = 0; j < 5; j++)
	// 		for (int k = 0; k < 5; k++)
	// 			cout << stb_perlin_noise3_seed(i, j, k, 0, 0, 0, 8) << endl;
	

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.

	glutDisplayFunc(render);
    glutReshapeFunc(changeSize);

	glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
    glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseKey);

	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
	glutMouseWheelFunc(mouseWheel);
 
	glutMainLoop();
 
	return 1;
}