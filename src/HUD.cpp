#include "../include/header.hpp"
#include "../include/HUD.hpp"

void drawHUD() {
    setOrthographicProjection(); 

	glDisable(GL_TEXTURE_2D);
	fpsCalc();
	renderBitmapString(5, 15, 0, GLUT_BITMAP_HELVETICA_12, fps);					// draw FPS
	renderBitmapString(WIDTH / 2, HEIGHT / 2, 0, GLUT_BITMAP_TIMES_ROMAN_24, "+");	// draw crosshair
	glEnable(GL_TEXTURE_2D);
	
	drawInventory();
	drawInventorySelector();

	restorePerspectiveProjection(); 
}

void drawInventory() {
	glTranslatef((WIDTH / 2) - invWidth / 2, HEIGHT - invHeight - OFFSET, 0);
	glBindTexture(GL_TEXTURE_2D, hud[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex2f(0, invHeight);
		glTexCoord2f(1, 1); glVertex2f(invWidth, invHeight);
		glTexCoord2f(1, 0); glVertex2f(invWidth, 0);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
	glEnd();
}

void drawInventorySelector() {
	int w = 24 * 2;	
	int h = 24 * 2;
	glPushMatrix();
	glTranslatef((invWidth / 9) * invSelector, -5, 0);
	glBindTexture(GL_TEXTURE_2D, hud[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1); glVertex3f(0, h, 1);
		glTexCoord2f(1, 1); glVertex3f(w, h, 1);
		glTexCoord2f(1, 0); glVertex3f(w, 0, 1);
		glTexCoord2f(0, 0); glVertex3f(0, 0, 1);
	glEnd();
	glPopMatrix();
}
