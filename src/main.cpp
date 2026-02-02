#include "points.h"
#include "raylib-cpp.hpp"
#include "renderer.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window graphicWindow(600, 600, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    Point3D a3D(300, 0, 1);
    Point3D b3D(-300, 0, 1);
    Point3D c3D(0, 300, 1);
    Point3D d3D(0, -300, 1);

    Point3D e3D(300, 0, 10);
    Point3D f3D(-300, 0, 10);
    Point3D g3D(0, 300, 10);
    Point3D h3D(0, -300, 10);

    vector<Point3D> points3D = {a3D, b3D, c3D, d3D, e3D, f3D, g3D, h3D};
    vector<Point2D> points2D;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto &p : points3D)
        {
            p.z+=0.01;
            Renderer::render(p);
        }

        EndDrawing();
    }
}
