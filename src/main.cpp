#include <GLUT/glut.h> //подключаем заголовочный файл glut.h
#include <math.h> 
#include <iostream>
using namespace std;

#define WIDTH 800
#define HEIGHT 600

// угол поворота камеры
float angle=0.0;
float speed = 3.0;
// координаты вектора направления движения камеры
float lx=0.0f,lz=-speed;
// XZ позиция камеры
float x=0.0f, z=-0.0f;
//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float deltaAngle = 0.0f;
float deltaMove = 0;

void computePos(float deltaMove) 
{
	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
}
 
void computeDir(float deltaAngle)
{
	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
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

void makeABlock() {
    int pos = 1;

    // Front
	glBegin(GL_QUADS);
		glVertex3f(-pos, -pos, pos);
		glVertex3f(-pos,  pos, pos);
		glVertex3f( pos,  pos, pos);
		glVertex3f( pos, -pos, pos);
	glEnd();

    // Back
    glBegin(GL_QUADS);
		glVertex3f(-pos, -pos, -pos);
		glVertex3f(-pos,  pos, -pos);
		glVertex3f( pos,  pos, -pos);
		glVertex3f( pos, -pos, -pos);
	glEnd();

    // Left
    glBegin(GL_QUADS);
		glVertex3f(-pos, -pos, -pos);
		glVertex3f(-pos, -pos,  pos);
		glVertex3f(-pos,  pos,  pos);
		glVertex3f(-pos,  pos, -pos);
	glEnd();

    // Right
    glBegin(GL_QUADS);
		glVertex3f(pos, -pos, -pos);
		glVertex3f(pos, -pos,  pos);
		glVertex3f(pos,  pos,  pos);
		glVertex3f(pos,  pos, -pos);
	glEnd();

    // Top
    glBegin(GL_QUADS);
		glVertex3f( pos, pos, -pos);
		glVertex3f( pos, pos,  pos);
		glVertex3f(-pos, pos,  pos);
		glVertex3f(-pos, pos, -pos);
	glEnd();

    // Bottom
    glBegin(GL_QUADS);
		glVertex3f( pos, -pos, -pos);
		glVertex3f( pos, -pos,  pos);
		glVertex3f(-pos, -pos,  pos);
		glVertex3f(-pos, -pos, -pos);
	glEnd();
}

void renderScene(void) {
    if (deltaMove)
		computePos(deltaMove);
	if (deltaAngle)
		computeDir(deltaAngle);

 // Очистка буфера цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();
	// установить камеру
	gluLookAt(   x, 1.0f,     z,
		  x+lx, 1.0f,  z+lz,
		  0.0f, 1.0f,  0.0f );
 
    
    makeABlock();

 
	glutSwapBuffers();
}

void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_LEFT:
			deltaAngle = -0.01f;
			break;
		case GLUT_KEY_RIGHT:
			deltaAngle = 0.01f;
			break;
		case GLUT_KEY_UP:
			deltaMove = 0.5f;
			break;
		case GLUT_KEY_DOWN:
			deltaMove = -0.5f;
			break;
	}
}

void releaseKey(int key, int x, int y) {
 
	switch (key) {
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT: 
			deltaAngle = 0.0f;
			break;
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN: 
			deltaMove = 0;
			break;
	}
}

int main(int argc, char **argv) {
 
	// Инициализация GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutSpecialFunc(pressKey);
    // Новые функции для регистрации
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
 
	// Основной цикл GLUT
	glutMainLoop();
 
	return 1;
}