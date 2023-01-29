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
        bool visibility;
        bool _isTextured;
        bool hover;
        int texture;
        string text;
        struct _size size;
        struct _color color;
        struct _color text_color;

        void move(int x, int y);
        void drawText();

    public:
        Button();
        void setButtonColor(int r, int g, int b);
        void setTextColor(int r, int g, int b);
        void addText(string text, int r, int g, int b);
        void setTexture(GLuint texture);
        void draw(int x, int y);
        bool isHovered(int x, int y);
        void setHover(bool hover);
        void setVisible(bool visibility);
        bool isVisible();
};

#endif