// krzywe_beziera.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "raylib.h"
#include <fstream>
#include <string>
#include <sstream>


#include "Button.h"
#include "iterator.h"
#include "Bezier_curve.h"
#include "Work_space.h"
#include "text_box.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define WORKSPACE_WIDTH  SCREEN_WIDTH * 0.7
#define WORKSPACE_HEIGHT SCREEN_HEIGHT * 0.8


class Paint {
public:
    Color color;
    int size;
    Vector2 pos;
    Paint(Color color, int size, Vector2 pos) {
        this->color = color;
        this->size = size;
        this->pos = pos;
    }
    void painting(Vector2 v) {
        pos = v;
    }
    void set_color(Color color) {
        this->color = color;
    }
};

class Pencil {

    Color color;
    int size;
    std::vector<Paint> paint;
public:
    Pencil(Color color, int size) {
        this->color = color;
        this->size = size;
    }
    void increase() {
        size++;
    }
    void decrease() {
        size--;
    }
    void set_color(Color color) {
        this->color = color;        
    }
    void painting(Vector2 p) {
        paint.push_back(Paint(color, size, p));
    }
    void draw() {
        for (auto element : paint) {
            DrawCircleV(element.pos, size, element.color);
        }
    }
};


std::vector<Bezier_curve> jakas_funkcja_bez_konkretnej_nazwy() {
    std::ifstream file("dane.txt");
    std::vector<Bezier_curve> curve;
    float x, y;
    int size;
    int l = 0;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            l = 0;
            for (char znak : line) {
                if (isspace(znak)) {
                    l++;
                }
            }
            if (l == 0) {
                ss >> size;
                curve.push_back(Bezier_curve(10, BLACK));
            }
            else if (l == 1) {
                ss >> x >> y;
                curve.back().add_point({x,y});
            }
        }
    }
    file.close();

    return curve;
}

int main()
{
    std::vector<Bezier_curve> curvee = jakas_funkcja_bez_konkretnej_nazwy();
    for (int i = 0; i < curvee.size(); i++) {
        curvee[i].calculate_bcurve();
    }

    Work_space work_space = Work_space(70,70, WORKSPACE_WIDTH, WORKSPACE_HEIGHT, 5);
    Work_space tools = Work_space(WORKSPACE_WIDTH + 70*2, 70, 174, WORKSPACE_HEIGHT, 5);
    Iterator iterator = Iterator();
    Pencil pencils = Pencil(BLACK , 3);

    Button pencil = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 0, 139, 50, BROWN);
    pencil.set_text("Kredka");
    Button bezier = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 1, 139, 50, BROWN);
    bezier.set_text("Bezier");
    Button button3 = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 2, 139, 50, BROWN);
    button3.set_text("Pokaz punkty\n kontrolne");
    button3.set_text_size(17);
    Button c_red = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 3, 139, 50, RED);
    Button c_black = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 4, 139, 50, BLACK);
    Button c_green = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 5, 139, 50, GREEN);
    Button c_pink = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 6, 139, 50, PINK);
    Button c_blue = Button(WORKSPACE_WIDTH + 160, 90 + 70 * 7, 139, 50, BLUE);


    Button read = Button(0, 0, 90, 30, BLUE);
    read.set_text("Wczytaj Punkty");
    read.set_text_size(25);
    read.set_text_pos(5, 5);
    Text_box save_file = Text_box(50, 50, 10, 10, RED);
    bool show_save = false;


    Vector2 mouse_pos = GetMousePosition();
        
    std::vector<Bezier_curve> curves;
    curves.push_back(Bezier_curve(30, BLACK));
    iterator.increase_size();

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "adasdas");
   
    bool move_point = false;
    int r = 0;
    Color pencil_color = BLACK;
    int tool = 0;
    bool draw_control = true;

    SetTargetFPS(60);

    while (!WindowShouldClose()){
        mouse_pos = GetMousePosition();

        switch (tool)
        {
        case 0: // kretka
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if (work_space.check_if_in_range(mouse_pos)) {
                    pencils.set_color(pencil_color);
                    pencils.painting(mouse_pos);
                }
            }
            break;
        case 1: //bezier
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                Vector2 pos = GetMousePosition();
                int x = iterator.get_index() - 1;
                int s = 5;
                if (!curves[x].Points.size() < 1) {
                    for (int i = 0; i < curves[x].Points.size(); i++) {
                        if (pos.x > curves[x].Points[i].x - 5 && pos.y > curves[x].Points[i].y - 5) {
                            if (pos.x < curves[x].Points[i].x + s && pos.y < curves[x].Points[i].y + s) {
                                move_point = true;
                                r = i;
                            }
                        }
                    }
                }
                if (move_point) {
                    curves[iterator.get_index() - 1].Points[r] = mouse_pos;
                }
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                move_point = false;
            }
            if (IsKeyPressed(KEY_A)) {
                curves.push_back(Bezier_curve(10, pencil_color));
                iterator.increase_size();
                move_point = false;
            }

            if (IsKeyPressed(KEY_Q)) {
                iterator.move_up();
                move_point = false;
            }

            if (IsKeyPressed(KEY_W)) {
                curves.pop_back();
                iterator.decrease_size();
                move_point = false;
            }


            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                move_point = false;
                if (work_space.check_if_in_range(mouse_pos)) {
                    curves[iterator.get_index() - 1].add_point(mouse_pos);
                }
            }

            if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Z)) {
                curves[iterator.get_index() - 1].pop_point();
                move_point = false;
            }
            break;
        }
        //std::cout << mouse_pos.x << ", "<< mouse_pos.y << std::endl;
        //DrawRectangleV(mouse_pos, { 10, 10 }, RED);

        if (pencil.click()) {
            curves.push_back(Bezier_curve(10, pencil_color));
            iterator.increase_size();
            iterator.move_up();

            tool = 0;
            std::cout << tool << std::endl;
        }
        if (bezier.click()) {
            tool = 1;
            std::cout << tool << std::endl;
        }
        if (button3.click()) {
            if (draw_control) {
                draw_control = false;
            }
            else {
                draw_control = true;
            }
        }

        if (c_red.click()) {
            pencil_color = RED;
        }
        if (c_green.click()) {
            pencil_color = GREEN;
        }
        if (c_black.click()) {
            pencil_color = BLACK;
        }
        if (c_pink.click()) {
            pencil_color = PINK;
        }
        if (c_blue.click()) {
            pencil_color = BLUE;
        }


        BeginDrawing();
        ClearBackground(RAYWHITE);


        pencils.draw();
        work_space.draw_border();
        tools.draw_border();
        pencil.draw();
        bezier.draw();
        button3.draw();

        c_red.draw();
        c_black.draw();
        c_green.draw();
        c_pink.draw();
        c_blue.draw();

        read.draw();

        if (read.click()) {
            show_save = true;
        }
        if (show_save) {
            int i = 3;
            for (int i = 0; i < curvee.size(); i++) {
                curvee[i].drav_curve();
            }
        }


        DrawText("Rysownik", 70, 10, 50, BLACK);
        //DrawText(TextFormat("Ilosc punktow: %d", curve.Points.size()), 10, SCREEN_HEIGHT - 50, 50, BLACK);
        DrawText(TextFormat("Ilosc Krzywych: %d", iterator.get_size()), 10, SCREEN_HEIGHT - 50, 20, BLACK);
        DrawText(TextFormat("Numer Krzywej: %d", iterator.get_index()), 10, SCREEN_HEIGHT - 20, 20, BLACK);
        DrawRectangle(190, SCREEN_HEIGHT - 22, 20, 20, iterator.get_color(iterator.get_index()-1));
        DrawRectangle(300, SCREEN_HEIGHT - 22, 20, 20, pencil_color);

        for (int i = 0; i < curves.size(); i++) {
            curves[i].calculate_bcurve();
            curves[i].drav_curve();
            if (draw_control) {
                curves[i].drav_control_points();
            }
        }
        EndDrawing();
    }
    CloseWindow();
}

