#include <iostream>
#include "controller.h"

// Check key presses, decide movement
void Controller::handleInput() 
{
    // Reset Deltas
    movementDelta = raylib::Vector3(0.0f, 0.0f, 0.0f);
    rotationDelta = raylib::Vector3(0.0f, 0.0f, 0.0f);
    
    float pitch = GetMouseDelta().x   * mouseSensitivity;
    float yaw   = GetMouseDelta().y   * mouseSensitivity;
    float roll  = GetMouseWheelMove() * mouseSensitivity;
    
    if(IsKeyPressed(KEY_O)) controlMode = ControlMode::Cam;   // Camera
    if(IsKeyPressed(KEY_P)) controlMode = ControlMode::Shape; // Shape #TODO make selector for shapes
    
    // Decide change in x,y,z based on keyboard input i.e update the move Vector
    if (IsKeyDown(KEY_W)) movementDelta.SetY( moveSpeed); // UP
    if (IsKeyDown(KEY_S)) movementDelta.SetY(-moveSpeed); // Down
    if (IsKeyDown(KEY_A)) movementDelta.SetX(-moveSpeed); // Left
    if (IsKeyDown(KEY_D)) movementDelta.SetX( moveSpeed); // Right
    if (IsKeyDown(KEY_I)) movementDelta.SetZ( moveSpeed); // Forward
    if (IsKeyDown(KEY_K)) movementDelta.SetZ(-moveSpeed); // Backward

    if(IsKeyDown(KEY_R)) rotationDelta = Vector3{-yaw, -pitch, roll}; // Rotate by Mouse when key activated
}

// Move stuff
void Controller::update(World &world)
{   
    // Camera Mode
    if (controlMode == ControlMode::Cam ) {
        world.camera.move(movementDelta);
        world.camera.rotate(rotationDelta); 
    }

    //Individual shape mode
    else if (controlMode == ControlMode::Shape) {
        world.shapes[selectedShapeIndex].move(movementDelta);
        world.shapes[selectedShapeIndex].rotate(rotationDelta);
    }
        
    else
        std::cout << "invalid Move Mode";
}

