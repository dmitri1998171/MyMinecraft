#include "../../include/header.hpp"
#include "../../include/Button.hpp"
#include "../../include/UI.hpp"

map<string, Button*> buttons;

Button::Button() {
    isVisible = true;
    isTextured = false;
    texture = 0;

    size.x = 0;
    size.y = 0;
    size.w = invWidth;
    size.h = invHeight;

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
        renderBitmapString((size.w / 2) - (2 * OFFSET), (size.h / 2) + HEIGHT_OFFSET, 1, GLUT_BITMAP_TIMES_ROMAN_24, text.c_str());
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

void Button::setTexture(GLuint texture) {
    this->texture = texture;
    isTextured = true;
}

void Button::draw(int x, int y) {
    glPushMatrix();
        move(x, y);
        drawText();

        if(isTextured) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
        else 
            glColor3f(color.r, color.g, color.b);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(0, size.h, 1);
            glTexCoord2f(1, 1); glVertex3f(size.w, size.h, 1);
            glTexCoord2f(1, 0); glVertex3f(size.w, 0, 1);
            glTexCoord2f(0, 0); glVertex3f(0, 0, 1);
        glEnd();
	glDisable(GL_TEXTURE_2D);
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

