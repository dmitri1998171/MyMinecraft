#include "../include/header.hpp"
#include "../include/input.hpp"
#include "../include/UI.hpp"
#include "../include/draw.hpp"
#include "../include/Button.hpp"
#include "../include/world.hpp"


void changeSize(int w, int h) {
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio =  1.0 * w / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(45.0f, ratio, 1, 1000.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(600, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Minecraft");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable (GL_TEXTURE_2D);		// Работа с текстурами
	glEnable (GL_DEPTH_TEST);		// тест глубины
	// glEnable(GLUT_MULTISAMPLE);

	stbLoadTexture(&texture[GRASS_SIDE], "media/textures/grass_side.png", 4);
	stbLoadTexture(&texture[GRASS_TOP], "media/textures/grass_top.png", 4);
	stbLoadTexture(&texture[DIRT], "media/textures/dirt.png", 4);
	stbLoadTexture(&texture[BEDROCK], "media/textures/bedrock.png", 4);

	stbLoadTexture(&skybox[TOP], "media/textures/skybox/skybox_top.png", 4);
	stbLoadTexture(&skybox[SIDE], "media/textures/skybox/skybox_side.png", 4);
	stbLoadTexture(&skybox[BOTTOM], "media/textures/skybox/skybox_bottom.png", 4);
	
	stbLoadTexture(&ui[INVENTORY], "media/textures/GUI/inventory.jpg", 4);
	stbLoadTexture(&ui[INV_SELECTOR], "media/textures/GUI/inventorySelector.png", 4);
	stbLoadTexture(&ui[MAIN_MENU_BG], "media/textures/GUI/mainMenuBackground.png", 4);
	stbLoadTexture(&ui[TITLE], "media/textures/GUI/minecraft.png", 4);
	stbLoadTexture(&ui[BUTTON], "media/textures/GUI/button.png", 4);
	

	createButtons();
	createFlatWorld();

	// for (int i = 0; i < 5; i++)
	// 	for (int j = 0; j < 5; j++)
	// 		for (int k = 0; k < 5; k++)
	// 			cout << stb_perlin_noise3_seed(i, j, k, 0, 0, 0, 8) << endl;
	

	glutWarpPointer(WIDTH / 2, HEIGHT / 2);		// Установка курсора в поз.

	glutDisplayFunc(render);
    glutReshapeFunc(changeSize);

	// glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);
    glutSpecialFunc(pressSpecialKey);
	glutSpecialUpFunc(releaseSpecialKey);

	glutPassiveMotionFunc(mouseMove);
	glutMouseFunc(mouseButton);
	glutMouseWheelFunc(mouseWheel);
 
	glutMainLoop();
 
	return 1;
}