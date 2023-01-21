#ifndef UI_HPP
#define UI_HPP

void drawInventory();
void drawInventorySelector();
void setOrthographicProjection();
void restorePerspectiveProjection();
void renderBitmapString(float x, float y, float z, void *font, const char *string);
void renderStrokeFontString( float x, float y, float z, void *font, const char *string);
void stbLoadTexture(GLuint *tex, const char * filename, int req_channels);
void fpsCalc();
void drawTexture(GLuint *texture, int w, int h, int x, int y, int z = 0);
void addToInventory(int x, int y, int z);
void drawHUD();
void createButtons();

void drawDebugLines();
#endif