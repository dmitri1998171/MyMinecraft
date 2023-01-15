#include "../../include/header.hpp"
#include "../../include/UI.hpp"


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

void drawBackground(GLuint *texture) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(255, 255, 255);
	
	glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_QUADS);
		glTexCoord2f(1, 0); glVertex2f(0, HEIGHT);
		glTexCoord2f(0, 0); glVertex2f(WIDTH, HEIGHT);
		glTexCoord2f(0, 1); glVertex2f(WIDTH, 0);
		glTexCoord2f(1, 1); glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawTexture(GLuint *texture, int w, int h, int x, int y) {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3f(255, 255, 255);
	glTranslatef(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, *texture);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0, h);
		glTexCoord2f(1, 0); glVertex2f(w, h);
		glTexCoord2f(1, 1); glVertex2f(w, 0);
		glTexCoord2f(0, 1); glVertex2f(0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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