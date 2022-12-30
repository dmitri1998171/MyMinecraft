#ifndef UI_HPP
#define UI_HPP

void drawInventory();
void drawInventorySelector();
void setOrthographicProjection();
void restorePerspectiveProjection();
void renderBitmapString(float x, float y, float z, void *font, const char *string);
void renderStrokeFontString( float x, float y, float z, void *font, const char *string);
void fpsCalc();
void drawDebugLines();
#endif