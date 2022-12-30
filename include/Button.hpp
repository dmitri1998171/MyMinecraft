#include "header.hpp"

struct _size {
    int x;
    int y;
    int w;
    int h;
};

struct _color {
    int r;
    int g;
    int b;
};

class Button {
    private:
        struct _size size;
        struct _color color;
        struct _color text_color;
        string text;

        void move(int x, int y) {
            size.x = x;
            size.y = y;

            glTranslatef(size.x, size.y, 0);
        }

        void drawText() {
            if(text.size() > 0) {
	            glColor3f(text_color.r, text_color.g, text_color.b);
	            renderBitmapString((size.w / 2) - (2 * OFFSET), (size.h / 2) + HEIGHT_OFFSET, 0, GLUT_BITMAP_TIMES_ROMAN_24, text.c_str());
            }
        }

    public:
        Button() {
            size.x = 0;
            size.y = 0;
            size.w = invWidth;
            size.h = invHeight;

		// glBindTexture(GL_TEXTURE_2D, hud[0]);

            setButtonColor(255, 255, 255);
            setTextColor(255, 255, 255);
        }

        void setButtonColor(int r, int g, int b) {
            color.r = r;
            color.g = g;
            color.b = b;
        }

        void setTextColor(int r, int g, int b) {
            text_color.r = r;
            text_color.g = g;
            text_color.b = b;
        }

        void addText(string text, int r, int g, int b) {
            this->text = text;
            setTextColor(r, g, b);
        }

        void draw(int x, int y) {
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
};