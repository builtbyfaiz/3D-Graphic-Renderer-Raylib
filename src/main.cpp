#include "controller/controller.h"
#include "view/renderer.h"

#include <iostream>
#include <vector>

int main()
{
    raylib::Window graphicWindow(600, 600, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);
    
    Shape cube1("resources/cube1.txt");
    Shape cube2("resources/cube2.txt");
   
    World world;
    
    world.shapes.push_back(cube1);
    world.shapes.push_back(cube2);

    Renderer::pushWorldIntoView(world, 600);// Temp function

    while (!WindowShouldClose())
    {
        Controller::handleInput();
        Controller::update(world);
        Renderer::render(world);
    }
    return 0;
}