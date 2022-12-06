#include "../include/header.hpp"
#include "../include/UI.hpp"



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