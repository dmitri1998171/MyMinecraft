#include <iostream>
#include "../include/header.hpp"
#include "../include/input.hpp"

using namespace std;

void computePos(float deltaMove) 
{
	x += deltaMove * lx * 0.1f;
	y += deltaMove * ly * 0.1f;
	z += deltaMove * lz * 0.1f;
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
    if (deltaMove) {
		computePos(deltaMove);
        glutPostRedisplay();
    }

 // Очистка буфера цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();

    gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
 
    
    makeABlock();
	// angle += yaw;
 
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.
	glutSetCursor(GLUT_CURSOR_NONE);			// Скрыть курсор

	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

	glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
 
	glutMainLoop();
 
	return 1;
}