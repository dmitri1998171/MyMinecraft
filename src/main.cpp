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
float lx = 0.0f, ly = 0.0f, lz = -speed;
// XZ позиция камеры§
float x = 0.0f, y = 0, z = 0.0f;


//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float yaw = 0.0f;
float pitch = 0.0f;
float deltaMove = 0;
int delta_x = -1;
int delta_y = -1;


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

void pressKey(int key, int xx, int yy) {
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.5f; break;
		case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
	}

	glutPostRedisplay();
} 
 
void releaseKey(int key, int x, int y) { 	
	switch (key) {
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : deltaMove = 0;break;
	}
} 

void mouseMove(int x, int y) { 	

	// Перевод от коорд. курсора 0,0 к коорд. w/2, h/2
	// Чтобы камера вращалась не только влево и вниз (увелич. коорд. относ. 0,0)
	delta_x = (WIDTH / 2) - x;
	delta_y = (HEIGHT / 2) - y;

	yaw = -delta_x * 0.001f;
	pitch = -delta_y * 0.001f;

	// update camera's direction
	lx = sin(angle + yaw);
	ly = -sin(angle + pitch);
	lz = -cos(angle + yaw);

	glutPostRedisplay();
}
 
void mouseButton(int button, int state, int x, int y) {
	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
 
		// when the button is released
		if (state == GLUT_UP) {

		}
		else  {// state = GLUT_DOWN

		}
	}
}

int main(int argc, char **argv) {
	// Инициализация GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.
	glutSetCursor(GLUT_CURSOR_NONE);			// Скрыть курсор

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Новые функции для регистрации
	glutIgnoreKeyRepeat(1);
    glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

    // регистрируем две новые функции
	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
 
	// Основной цикл GLUT
	glutMainLoop();
 
	return 1;
}