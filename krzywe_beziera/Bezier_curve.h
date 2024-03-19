#include <iostream>
#include <vector>
#include "raylib.h"
#include <cassert>


int silnia(int n) {
    assert(n >= 0);
    if (n < 1) {
        return 1;
    }
    else {
        return n * silnia(n - 1);
    }
}



int newton(int n, int k) {
    assert(n >= 0);
    assert(n >= k);
    int licznik = silnia(n);
    int mianownik = silnia(k) * silnia(n - k);
    return licznik / mianownik;
}



class Bezier_curve {
public:
    std::vector<Vector2> Points;
    std::vector<Vector2> T;
    int density;
    Color color;
    Bezier_curve(int density, Color color) {
        this->density = density;
        this->color = color;
    }

    void set_color(Color c) {
        color = c;
    }

    void add_point(Vector2 P) {
        Points.push_back(P);
    }

    void pop_point() {
        if (Points.size() > 0) {
            Points.pop_back();
        }
    }

    Vector2 calculate_sum(float t) {
        float sum_x = 0;
        float sum_y = 0;
        int n = Points.size() - 1;
        for (int i = 0; i <= n; i++) {
            sum_x += newton(n, i) * pow(1 - t, n - i) * pow(t, i) * Points[i].x;
            sum_y += newton(n, i) * pow(1 - t, n - i) * pow(t, i) * Points[i].y;

        }
        return { sum_x, sum_y };
    }

    void calculate_bcurve() {
        T.clear();
        for (int i = 0; i <= density; i++) {
            float t = (float)i / density;
            Vector2 xx = calculate_sum(t);
            T.push_back(xx);
        }
    }
    void drav_curve() {
        int n = T.size() - 1;
        for (int i = 0; i < n; i++) {
            DrawLineV(T[i], T[i + 1], color);
        }
    }

    void drav_control_points() {
        for (auto element : Points) {
            DrawCircleV(element, 5, color);
        }
    }

    void drav_curveP() {
        int n = T.size();
        for (int i = 0; i < n; i++) {
            DrawPixelV(T[i], color);
        }
    }
};
