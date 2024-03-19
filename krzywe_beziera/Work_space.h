#include <iostream>
#include "raylib.h"

class Work_space {
    int pos_x;
    int pos_y;
    int width;
    int height;
    int thick;

public:
    Work_space() {}

    Work_space(int pos_x, int pos_y, int width, int height, int thick) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
        this->thick = thick;
    }

    void draw_border() {
        DrawRectangle(pos_x, pos_y, width, thick, RED);
        DrawRectangle(pos_x + width, pos_y, thick, height, RED);
        DrawRectangle(pos_x + thick, pos_y + height, width, thick, RED);
        DrawRectangle(pos_x, pos_y + thick, thick, height, RED);
    }

    bool check_if_in_range(Vector2 v) {
        if (v.x < pos_x || v.y < pos_y) {
            //std::cout << "poza\n";
            return false;
        }
        if (v.x > width + pos_x || v.y > height + pos_y) {
            //std::cout << "poza\n";
            return false;
        }
        return true;
    }
};