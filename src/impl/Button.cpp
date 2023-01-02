#include "../../include/header.hpp"
#include "../../include/Button.hpp"
#include "../../include/UI.hpp"

Button::Button() {
    size.x = 0;
    size.y = 0;
    size.w = invWidth;
    size.h = invHeight;
    isVisible = true;

// glBindTexture(GL_TEXTURE_2D, ui[0]);

    setButtonColor(255, 255, 255);
    setTextColor(255, 255, 255);
}

void Button::move(int x, int y) {
    size.x = x;
    size.y = y;

    glTranslatef(size.x, size.y, 0);
}

void Button::drawText() {
    if(text.size() > 0) {
        glColor3f(text_color.r, text_color.g, text_color.b);
        renderBitmapString((size.w / 2) - (2 * OFFSET), (size.h / 2) + HEIGHT_OFFSET, 0, GLUT_BITMAP_TIMES_ROMAN_24, text.c_str());
    }
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

bool Button::isClicked(int x, int y) {
    if(this->isVisible == true) {
        if(x > size.x && x < (size.x + size.w))
            if(y > size.y && y < (size.y + size.h))
                return true;
    }
    
    return false;
}

void Button::setVisible(bool visibility) {
    this->isVisible = visibility;
}

