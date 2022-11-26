#include <GLUT/glut.h> //подключаем заголовочный файл glut.h
 
#define WIDTH 800
#define HEIGHT 600

void renderScene(void) {
 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.0,0.5,0.0);
		glVertex3f(0.5,-0.5,0.0);
	glEnd();
 
	glutSwapBuffers();
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
 
	// Основной цикл GLUT
	glutMainLoop();
 
	return 1;
}