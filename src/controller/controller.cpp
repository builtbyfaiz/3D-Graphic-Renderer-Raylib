#include <iostream>
#include "controller/controller.h"


// Check key presses, decide movement
void Controller::handleInput() 
{
    // By default Do no movement, reset delta
    delta = raylib::Vector3{0,0,0};

    if(IsKeyPressed(KEY_O)) moveMode = 0; // Camera
    if(IsKeyPressed(KEY_P)) moveMode = 1; // Shape #TODO make selector for shapes

    // Decide change in x,y,z based on input i.e construct the move Vector
    if (IsKeyDown(KEY_D)) delta.x += moveSpeed;
    if (IsKeyDown(KEY_A)) delta.x -= moveSpeed;
    
    if (IsKeyDown(KEY_W)) delta.y += moveSpeed;
    if (IsKeyDown(KEY_S)) delta.y -= moveSpeed;

    if (IsKeyDown(KEY_I)) delta.z += moveSpeed;
    if (IsKeyDown(KEY_K)) delta.z -= moveSpeed;
}

// Move stuff
void Controller::update(World &world)
{   
    //Individual shape mode
    if (moveMode == 1)
        world.shapes[selectedShapeIndex].move(delta);

    // Camera Mode
    else if (moveMode == 0)
        world.camera.move(delta);

    else
        std::cout << "invalid Move Mode";
}

int  Controller::moveSpeed          = 1;
int  Controller::selectedShapeIndex = 0;
bool Controller::moveMode           = 0;

raylib::Vector3 Controller::delta{0.0f, 0.0f, 0.0f};

