#include <iostream>
#include "raylib.h"
#include <vector>

class Iterator {
    int i;
    int max_size;
    std::vector<Color> colors;
public:
    Iterator() {
        i = 1;
        max_size = 0;
        colors.push_back(BLACK);
        colors.push_back(PINK);
        colors.push_back(LIME);
        colors.push_back(MAROON);
        colors.push_back(MAGENTA);
        colors.push_back(GREEN);
        colors.push_back(YELLOW);
        colors.push_back(LIGHTGRAY);
        colors.push_back(RED);
        colors.push_back(DARKPURPLE);
        colors.push_back(BEIGE);
    }
    void increase_size() {
        max_size++;
    }
    Color get_color(int x) {
        return colors[x];
    }

    void decrease_size() {
        max_size--;
        i--;
    }

    void move_up() {
        i++;
        if (i > max_size) {
            i = 1;
        }
    }
    void move_down() {
        i--;
        if (i < 1) {
            i = max_size;
        }
    }
    int get_index() {
        return i;
    }

    int get_size() {
        return max_size;
    }
};