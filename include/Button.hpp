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
        Button();
        void setButtonColor(int r, int g, int b);
        void setTextColor(int r, int g, int b);
        void addText(string text, int r, int g, int b);
        void draw(int x, int y);
        bool isClicked(int x, int y);
};