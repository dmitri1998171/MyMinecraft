#include "../include/header.hpp"
#include "../include/input.hpp"
#include "../include/SOIL/SOIL.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

// GLuint texture;

static unsigned int texture[2]; // Array of texture indices.
static int id = 0;

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
	glDisable(GL_TEXTURE_2D);

    // // Back
    // glBegin(GL_QUADS);
	// 	glColor3f(255, 0, 0);
	// 	glVertex3f(-pos, -pos, -pos);
	// 	glVertex3f(-pos,  pos, -pos);
	// 	glVertex3f( pos,  pos, -pos);
	// 	glVertex3f( pos, -pos, -pos);
	// glEnd();

    // // Left
    // glBegin(GL_QUADS);
	// 	glColor3f(255, 255, 255);
	// 	glVertex3f(-pos, -pos, -pos);
	// 	glVertex3f(-pos, -pos,  pos);
	// 	glVertex3f(-pos,  pos,  pos);
	// 	glVertex3f(-pos,  pos, -pos);
	// glEnd();

    // // Right
    // glBegin(GL_QUADS);
	// 	glVertex3f(pos, -pos, -pos);
	// 	glVertex3f(pos, -pos,  pos);
	// 	glVertex3f(pos,  pos,  pos);
	// 	glVertex3f(pos,  pos, -pos);
	// glEnd();

    // // Top
    // glBegin(GL_QUADS);
	// 	glVertex3f( pos, pos, -pos);
	// 	glVertex3f( pos, pos,  pos);
	// 	glVertex3f(-pos, pos,  pos);
	// 	glVertex3f(-pos, pos, -pos);
	// glEnd();

    // // Bottom
    // glBegin(GL_QUADS);
	// 	glVertex3f( pos, -pos, -pos);
	// 	glVertex3f( pos, -pos,  pos);
	// 	glVertex3f(-pos, -pos,  pos);
	// 	glVertex3f(-pos, -pos, -pos);
	// glEnd();
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


GLuint LoadTexture(GLuint *tex, const char * filename, int width, int height)
{
	//bmp 24 bit
	unsigned char * data;
	unsigned char R,G,B;
	FILE * file;

	//open .bmp
	file = fopen(filename, "rb");

	if(file == NULL) {
		cout << "ERROR: Can't load a texture!" << endl;
		return 0;
	}

	//get memory for data
	data =(unsigned char *)malloc(width * height * 3);

	//data skip offset 
	// fseek(file,128,0);
	//read file to data
	fread(data, width * height * 3, 1, file);
	//close file
	fclose(file);

	//transpose R,G,B values
	int index;
	for(int i = 0; i < width * height; ++i) {
		B = data[index]; G = data[index+1]; R = data[index+2];
		data[index] = R; data[index+1] = G; data[index+2] = B;
		index = i*3;
	}

	//create a texture
	glGenTextures(1, tex);
	glBindTexture(GL_TEXTURE_2D, *tex);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//free memory
	free(data);
	return 0;
}

void stbLoadTexture(const char * filename, int req_channels) {
	/*
	req_channels:
		BMP-file = 0  
		JPEG-file = 4  
	*/
	int width = 0, height = 0, channels = 0;

	stbi_set_flip_vertically_on_load(true);  
	stbi_uc *image = stbi_load( filename, &width, &height, &channels, req_channels );

	if ( image != nullptr ) {
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		stbi_image_free( image );
	}
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	glEnable (GL_TEXTURE_2D);
	// LoadTexture(&texture[0], "media/textures/grass512x512.bmp", 512, 512);
	stbLoadTexture("media/textures/grass512x512.jpeg", 4);

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