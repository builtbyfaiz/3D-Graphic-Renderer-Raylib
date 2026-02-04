#include "controller.h"

// Check key presses, decide movement
void Controller::handleInput() {

    // By default Do no movement
    raylib::Vector3 moveVec(0,0,0);
    // camMove   = {0,0,0};
    // shapeMove = {0,0,0};
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
    world.camera.move(camMove);
    world.shapes[selectedShapeIndex].move(shapeMove);
}

int             Controller::moveSpeed          = 1;
int             Controller::selectedShapeIndex = 0;
bool            Controller::moveMode           = 0;
raylib::Vector3 Controller::camMove(0,0,0);
raylib::Vector3 Controller::shapeMove(0,0,0);

