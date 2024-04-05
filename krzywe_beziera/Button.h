#include "raylib.h"
#include <iostream>


class Button {
    int pos_x; int pos_y; int width; int height;
    Color color;
    std::string text;
    int text_size;
    int test_pos_x;
    int test_pos_y;
public:
    Button(int pos_x, int pos_y, int width, int height, Color color) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->width = width;
        this->height = height;
        this->color = color;
        text_size = height * 0.7;
        test_pos_x = pos_x + 10;
        test_pos_y = pos_y + 10;
    }
    bool click() {
        Vector2 v = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (v.x > pos_x && v.y > pos_y && v.x < width + pos_x && v.y < height + pos_y) {
                return true;
            }
        }
        return false;
    }
    void set_text(std::string text) {
        this->text = text;
    }
    void set_text_size(int x) {
        text_size = x;
    }
    void set_text_pos(int x, int y) {
        test_pos_x = x;
        test_pos_y = y;
    }
    void draw() {
        DrawRectangle(pos_x, pos_y, width, height, color);
        DrawText(text.c_str(), test_pos_x, test_pos_y, text_size, BLACK);
    }
};