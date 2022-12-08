#include "../include/header.hpp"
#include "../include/UI.hpp"


void drawInventory() {
	glTranslatef((WIDTH / 2) - invWidth / 2, HEIGHT - invHeight - OFFSET, 0);
	glBindTexture(GL_TEXTURE_2D, hud[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex2f(0, invHeight);
		glTexCoord2f(1, 1); glVertex2f(invWidth, invHeight);
		glTexCoord2f(1, 0); glVertex2f(invWidth, 0);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
	glEnd();
}

void drawInventorySelector() {
	int w = 24 * 2;	
	int h = 24 * 2;
	glPushMatrix();
	glTranslatef((invWidth / 9) * invSelector, -5, 0);
	glBindTexture(GL_TEXTURE_2D, hud[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f(0, h, 1);
		glTexCoord2f(1, 1); glVertex3f(w, h, 1);
		glTexCoord2f(1, 0); glVertex3f(w, 0, 1);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 1);
	glEnd();
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////////


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

void renderBitmapString(float x, float y, float z, void *font, char *string) {
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void renderStrokeFontString( float x, float y, float z, void *font, char *string) {
	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);
 
	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}
 
	glPopMatrix();
}

// Вычисление количества кадров в секунду
void fpsCalc() {
	frame++;
 
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(fps,"FPS:%4.2f", frame*1000.0 / (time-timebase));
		timebase = time;
		frame = 0;
	}
}