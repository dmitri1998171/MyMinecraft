#include "../include/UI.hpp"
#include "../include/Button.hpp"

Button::Button() {
    size.x = 0;
    size.y = 0;
    size.w = invWidth;
    size.h = invHeight;

// glBindTexture(GL_TEXTURE_2D, hud[0]);

    setButtonColor(255, 255, 255);
    setTextColor(255, 255, 255);
}

void Button::setButtonColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

void Button::setTextColor(int r, int g, int b) {
    text_color.r = r;
    text_color.g = g;
    text_color.b = b;
}

void Button::addText(string text, int r, int g, int b) {
    this->text = text;
    setTextColor(r, g, b);
}

void Button::draw(int x, int y) {
    glPushMatrix();
        move(x, y);
        drawText();

        glColor3f(color.r, color.g, color.b);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, size.h);
            glTexCoord2f(1, 1); glVertex2f(size.w, size.h);
            glTexCoord2f(1, 0); glVertex2f(size.w, 0);
            glTexCoord2f(0, 0); glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
}
