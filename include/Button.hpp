#ifndef BUTTON_HPP
#define BUTTON_HPP

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

        void move(int x, int y);
        void drawText();

    public:
        Button();
        void setButtonColor(int r, int g, int b);
        void setTextColor(int r, int g, int b);
        void addText(string text, int r, int g, int b);
        void draw(int x, int y);
        bool isClicked(int x, int y);
};

#endif