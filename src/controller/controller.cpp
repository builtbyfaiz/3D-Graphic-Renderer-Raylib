#include <iostream>
#include "controller/controller.h"
#include "model/vector3D.h"

// Check key presses, decide movement
void Controller::handleInput() 
{
    // By default Do no movement
    Vec3 moveVec(0,0,0);
    camMove   = {0,0,0};
    shapeMove = {0,0,0};
    
    // if(GetKeyPressed == 0) return;

    if(IsKeyPressed(KEY_O)) moveMode=0; // Camera
    if(IsKeyPressed(KEY_P)) moveMode=1; // Shape #TODO make selector

    // Decide change in x,y,z based on input
    if (IsKeyDown(KEY_D)) moveVec.x += moveSpeed;
    if (IsKeyDown(KEY_A)) moveVec.x -= moveSpeed;
    
    if (IsKeyDown(KEY_W)) moveVec.y += moveSpeed;
    if (IsKeyDown(KEY_S)) moveVec.y -= moveSpeed;

    if (IsKeyDown(KEY_I)) moveVec.z += moveSpeed;
    if (IsKeyDown(KEY_K)) moveVec.z -= moveSpeed;

    if(moveMode == 0) camMove   = moveVec;
    if(moveMode == 1) shapeMove = moveVec;
}

// Move stuff
void Controller::update(World &world)
{
    //Individual shape mode
    if (moveMode == 1)
        world.shapes[selectedShapeIndex].move(shapeMove);

    // Camera Mode
    else if (moveMode == 0)
        world.camera.move(camMove);

    else
        std::cout << "invalid Move Mode";
}

int  Controller::moveSpeed          = 1;
int  Controller::selectedShapeIndex = 0;
bool Controller::moveMode           = 0;

Vec3 Controller::camMove(0,0,0);
Vec3 Controller::shapeMove(0,0,0);

