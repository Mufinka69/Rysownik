#include <raylib.h>

class Text_box {
	int pos_x;
	int pos_y;
	int width;
	int height;
    Color color;
	char text[255] = "adsadsada";
public:
    Text_box(int pos_x, int pos_y, int width, int height, Color color) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
        this->color = color;
    }


    void draw() {
        DrawRectangle(pos_x, pos_y, width, height, color);
        DrawText(text, pos_x + 3, pos_y + 3, height, BLACK);
    }

};