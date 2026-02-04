#include "raylib-cpp.hpp"
#include "controller.h"
#include "renderer.h"
#include "vector3D.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    raylib::Window graphicWindow(600, 600, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    float h = 100.f; // Cube face distance from origin, Used to create symmetric cube
    Shape cube, cube2;

    cube.vertices = {
        {-h, -h, -h}, {h, -h, -h}, {h, h, -h}, {-h, h, -h},
        {-h, -h,  h}, {h, -h,  h}, {h, h,  h}, {-h, h,  h}
    };

    cube2.vertices = cube.vertices;

    cube.edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };

    cube2.edges = cube.edges;
    cube2.setColor(RED);

    // create a copy of original world to turn into camera view #TODO make this automatic in render pipeline
    World world;
    world.shapes.push_back(cube);
    world.shapes.push_back(cube2);


    World worldToRender = world; 
    
    while (!WindowShouldClose())
    {
        Controller::handleInput();
        Controller::update(world);
        worldToRender = world;
        Renderer::pushWorldIntoView(worldToRender, 600);// Temp function
        Renderer::render(worldToRender);
    }
    return 0;
}

