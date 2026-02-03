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

    float h =
        100.f; // Distance from Center {0,0,0} of the cube's faces, Used to create symmetric cube

    vector<Point3D> cube = {{-h, -h, -h}, {h, -h, -h}, {h, h, -h}, {-h, h, -h},
                            {-h, -h,  h}, {h, -h,  h}, {h, h,  h}, {-h, h,  h}};

    vector<pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };

    vector<Point2D> points2D;

    // Cube is at {0,0,0}, Camera is also at [0,0,0] so, Push cube forward to see it better
    for (auto &p : cube)
    {
        p.z += 500;
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto &p : cube)
        {
            p.x += 0.1;
            Renderer::renderShape(cube, edges);
        }

        EndDrawing();
    }
}
