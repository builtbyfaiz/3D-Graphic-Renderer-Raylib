#include <iostream>
#include "controller.h"

// Check key presses, decide movement
void Controller::handleInput() 
{
    // By default Do no movement, reset delta
    // Vector2 mouseDelta = GetMouseDelta();

    // float yaw   += mouseDelta.x * controlSpeed;   
    // float pitch += mouseDelta.y * controlSpeed;
    
    movementDelta = raylib::Vector3{0,0,0};
    
    if(IsKeyPressed(KEY_O)) controlMode = ControlMode::Cam; // Camera
    if(IsKeyPressed(KEY_P)) controlMode = ControlMode::Shape;; // Shape #TODO make selector for shapes

    // Decide change in x,y,z based on input i.e construct the move Vector
    if (IsKeyDown(KEY_A)) movementDelta.x -= controlSpeed;
    if (IsKeyDown(KEY_D)) movementDelta.x += controlSpeed;
    
    if (IsKeyDown(KEY_W)) movementDelta.y += controlSpeed;
    if (IsKeyDown(KEY_S)) movementDelta.y -= controlSpeed;

    if (IsKeyDown(KEY_I)) movementDelta.z += controlSpeed;
    if (IsKeyDown(KEY_K)) movementDelta.z -= controlSpeed;
}

// Move stuff
void Controller::update(World &world)
{   
    // Camera Mode
    if (controlMode == ControlMode::Cam )
        world.camera.move(movementDelta);
    
    //Individual shape mode
    else if (controlMode == ControlMode::Shape)
        world.shapes[selectedShapeIndex].move(movementDelta);
        
    else
        std::cout << "invalid Move Mode";
}

