#include "../include/header.hpp"
#include "../include/input.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/dependencies/stb_image.h"
#define STB_PERLIN_IMPLEMENTATION
#include "../include/dependencies/stb_perlin.h"

GLuint texture[4];
// переменные для вычисления количества кадров в секунду
int frame;
long time, timebase;
char s[50];

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
}

void restorePerspectiveProjection() {
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

void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string) {
	char *c;
	int x1=x;

	for (c=string; *c != '\0'; c++) {
		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
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
		sprintf(s,"FPS:%4.2f", frame*1000.0 / (time-timebase));
		timebase = time;
		frame = 0;
	}
}

void renderScene(void) {
	computePos(deltaMove);

 // Очистка буфера цвета и глубины.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// обнулить трансформацию
	glLoadIdentity();

    gluLookAt(x, y, z,
		  x + lx, y + ly, z + lz,
		  0.0f, 1.0f, 0.0f);
 
	int fieldSize = 30;
	drawFlatWorld(fieldSize);

	fpsCalc();

	setOrthographicProjection(); 
	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5, 15 ,0, GLUT_BITMAP_HELVETICA_12, s);
	glPopMatrix();
	restorePerspectiveProjection(); 


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
	
	glEnable (GL_TEXTURE_2D);		// Работа с текстурами
	glEnable (GL_DEPTH_TEST);		// тест глубины
	// glEnable(GL_CULL_FACE);			// occlusion query
	// glCullFace(GL_FRONT);

	stbLoadTexture(&texture[0], "media/textures/grass_side.png", 4);
	stbLoadTexture(&texture[1], "media/textures/grass_top.png", 4);
	stbLoadTexture(&texture[2], "media/textures/dirt.png", 4);
	stbLoadTexture(&texture[3], "media/textures/bedrock.png", 4);

	// for (int i = 0; i < 5; i++)
	// 	for (int j = 0; j < 5; j++)
	// 		for (int k = 0; k < 5; k++)
	// 			cout << stb_perlin_noise3_seed(i, j, k, 0, 0, 0, 8) << endl;
	

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