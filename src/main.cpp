#include "../include/header.hpp"
#include "../include/input.hpp"
#include "../include/SOIL/SOIL.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

GLuint texture[3];

void computePos(float deltaMove) {
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
    float pos = 1;

   // Activate a texture.
   glBindTexture(GL_TEXTURE_2D, texture[0]);
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

   	glBindTexture(GL_TEXTURE_2D, texture[1]);

    // Top
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, pos, -pos);
	glEnd();

   	glBindTexture(GL_TEXTURE_2D, texture[2]);

    // Bottom
    glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f( pos, -pos, -pos);
		glTexCoord2f(1, 0); glVertex3f( pos, -pos,  pos);
		glTexCoord2f(1, 1); glVertex3f(-pos, -pos,  pos);
		glTexCoord2f(0, 1); glVertex3f(-pos, -pos, -pos);
	glEnd();
}

void renderScene(void) {
	glEnable(GL_TEXTURE_2D);

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
 
    glPushMatrix();
	glTranslatef(0, 0, -5);
	glRotatef(rotate_block, 0, 1, 0);

		// loadExternalTextures();
    	makeABlock();
   		// loadProceduralTextures();
		
	glPopMatrix();

   	// Specify how texture values combine with current surface color values.
   	// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

	glutSwapBuffers();

	glDisable(GL_TEXTURE_2D);
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
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free( image );
	}
	else {
		cout << "ERROR: Can't load a texture!" << endl;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	glEnable (GL_TEXTURE_2D);
	stbLoadTexture(&texture[0], "media/textures/grass_side.png", 4);
	stbLoadTexture(&texture[1], "media/textures/grass_top.png", 4);
	stbLoadTexture(&texture[2], "media/textures/dirt.png", 4);

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.
	glutSetCursor(GLUT_CURSOR_NONE);			// Скрыть курсор

	glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

	glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
    glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseKey);

	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
 
	glutMainLoop();
 
	return 1;
}