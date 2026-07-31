#include "controller/controller.h"
#include "view/renderer.h"
#include <iostream>
#include <vector>

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    raylib::Window graphicWindow(800, 800, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);
    DisableCursor();

    // Shape cube1("resources/cube1.txt");
    // Shape cube2("resources/cube2.txt");
    Shape dragon1("resources/dragon1.txt");
    Shape dragon2("resources/dragon2.txt");
   
    World world;
    
    world.shapes.push_back(dragon1);
    world.shapes.push_back(dragon2);

    Controller controller;
    Renderer renderer;

    while (!WindowShouldClose())
    {
        controller.handleInput();
        controller.update(world);
        renderer.render(world);
    }
    return 0;
}