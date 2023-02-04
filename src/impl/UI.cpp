#include "../../include/header.hpp"
#include "../../include/UI.hpp"
#include "../../include/Button.hpp"
#include "../../include/Inventory.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../include/dependencies/stb_image.h"

extern map<string, Button*> buttons;
extern Inventory inventory;

void setOrthographicProjection() {
	//переключения режима проецирования
	glMatrixMode(GL_PROJECTION);
	//Сохраняем предыдущую матрицу, которая содержит
        //параметры перспективной проекции
	glPushMatrix();
	//обнуляем матрицу
	glLoadIdentity();
	//устанавливаем 2D ортогональную проекцию
	gluOrtho2D(0, WIDTH, HEIGHT, 0);
	// возврата в режим обзора модели
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void restorePerspectiveProjection() {
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	//восстановить предыдущую матрицу проекции
	glPopMatrix();
	//вернуться в режим модели
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, float z, void *font, const char *string) {
	char *c;
	glRasterPos3f(x, y,z);
	for (c=strdup(string); *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString( float x, float y, float z, void *font, const char *string) {
	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);
 
	for (c=strdup(string); *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
 
	glPopMatrix();
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

// Вычисление количества кадров в секунду
void fpsCalc() {
	frame++;
 
	_time=glutGet(GLUT_ELAPSED_TIME);
	if (_time - timebase > 1000) {
		sprintf(fps,"FPS:%4.2f", frame*1000.0 / (_time-timebase));
		timebase = _time;
		frame = 0;
	}
}

void drawTexture(GLuint *texture, int w, int h, int x, int y, int z) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(255, 255, 255);
	glTranslatef(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(0, h, z);
		glTexCoord2f(1, 0); glVertex3f(w, h, z);
		glTexCoord2f(1, 1); glVertex3f(w, 0, z);
		glTexCoord2f(0, 1); glVertex3f(0, 0, z);
	glEnd();
	glPopMatrix();
	// glDisable(GL_TEXTURE_2D);
}

void drawHUD() {
    setOrthographicProjection(); 

	glDisable(GL_TEXTURE_2D);
	fpsCalc();
	renderBitmapString(5, 15, 1, GLUT_BITMAP_HELVETICA_12, fps);						// draw FPS
	renderBitmapString((WIDTH / 2) - 6, (HEIGHT / 2) + 6, 0.9, GLUT_BITMAP_TIMES_ROMAN_24, "+");	// draw crosshair
	glEnable(GL_TEXTURE_2D);
	
	inventory.drawInventory();

	restorePerspectiveProjection(); 
}

void createButtons() {
	buttons["play"] = new Button;
	buttons["play"]->setButtonColor(0, 255, 0);
	buttons["play"]->setTexture(ui[BUTTON]);
	buttons["play"]->addText("PLAY", 255, 255, 255);
	
	buttons["exit"] = new Button;
	buttons["exit"]->setButtonColor(255, 0, 0);
	buttons["exit"]->setTexture(ui[BUTTON]);
	buttons["exit"]->addText("EXIT", 255, 255, 255);
	
	buttons["continue"] = new Button;
	buttons["continue"]->setButtonColor(0, 255, 0);
	buttons["continue"]->setTexture(ui[BUTTON]);
	buttons["continue"]->addText("Continue", 255, 255, 255);
	
	buttons["main_menu"] = new Button;
	buttons["main_menu"]->setButtonColor(255, 0, 0);
	buttons["main_menu"]->setTexture(ui[BUTTON]);
	buttons["main_menu"]->addText("Main Menu", 255, 255, 255);
}

void drawDebugLines() {
	// ///////// Debug lines /////////////////////////////////

	glColor3f(0, 255, 0);
	glBegin(GL_LINES);
	glVertex2f(WIDTH / 2, 0);
	glVertex2f(WIDTH / 2, HEIGHT);
	glEnd();

	// -------------------------------------------------------

	glBegin(GL_LINES);
	glVertex2f(0, HEIGHT / 4);
	glVertex2f(WIDTH, HEIGHT / 4);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(0, HEIGHT / 2);
	glVertex2f(WIDTH, HEIGHT / 2);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(0, HEIGHT - (HEIGHT / 4));
	glVertex2f(WIDTH, HEIGHT - (HEIGHT / 4));
	glEnd();

	// ///////////////////////////////////////////////////////
}


