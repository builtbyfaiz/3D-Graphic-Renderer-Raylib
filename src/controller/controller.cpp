#include "controller.h"
#include <iostream>

// Check key presses, decide movement
void Controller::handleInput()
{
    // Reset Deltas
    movementDelta = raylib::Vector3(0.0f, 0.0f, 0.0f);
    rotationDelta = raylib::Vector3(0.0f, 0.0f, 0.0f);

    pitch = GetMouseDelta().x   * mouseSensitivity;
    yaw   = GetMouseDelta().y   * mouseSensitivity;
    roll  = GetMouseWheelMove() * mouseSensitivity * 10.0; // Provide boost to the wheels movement

    if (IsKeyDown(KEY_ESCAPE)) EnableCursor();

    if (IsKeyPressed(KEY_R)) toggleRotationMode();
    if (IsKeyPressed(KEY_C)) toggleControlMode();
    
     
    // Decide change in x,y,z based on keyboard input i.e update the move Vector
    if (IsKeyDown(KEY_W)) movementDelta.SetZ( moveSpeed);  // Forward
    if (IsKeyDown(KEY_S)) movementDelta.SetZ(-moveSpeed);  // Backward
    if (IsKeyDown(KEY_A)) movementDelta.SetX(-moveSpeed);  // Left
    if (IsKeyDown(KEY_D)) movementDelta.SetX( moveSpeed);  // Right
    if (IsKeyDown(KEY_E)) movementDelta.SetY( moveSpeed);  // UP
    if (IsKeyDown(KEY_Q)) movementDelta.SetY(-moveSpeed);  // Down

    if (IsKeyPressed(KEY_T)) selectedShapeIndex++;
}

// Move stuff
void Controller::update(World &world)
{
    if(rotationMode) 
        rotationDelta = Vector3{-yaw, -pitch, roll}; 
    
        // Camera Mode
    if (controlMode == ControlMode::Cam)
    {
        world.camera.move(movementDelta);
        world.camera.rotate(rotationDelta);
    }

    //Individual shape mode
    else if (controlMode == ControlMode::Shape)
    {
        selectedShapeIndex = selectedShapeIndex % world.shapes.size(); // Wrap to make it safe
        world.shapes[selectedShapeIndex].move(movementDelta);
        world.shapes[selectedShapeIndex].rotate(rotationDelta);
    }

    else
        std::cout << "invalid Move Mode";
}

// Toggles between controlling shapes or camera
void Controller::toggleControlMode()
{
    controlMode = (controlMode == ControlMode::Cam) ? ControlMode::Shape : ControlMode::Cam;
}

// Toggles rotations via mouse
void Controller::toggleRotationMode() 
{
    rotationMode = rotationMode == false ? true : false;
}