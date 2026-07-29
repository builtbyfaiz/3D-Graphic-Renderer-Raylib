#pragma once
#include "model/world.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep


// handles input, camera movement, shape movement
class Controller
{
  private:
    enum class ControlMode
    {
        Cam,  // Move / Rotate Camera
        Shape // Move / Rotate Shapes
    } controlMode{ControlMode::Cam};

  public:

    float moveSpeed          = 1.5;  // Control Speed of movement
    float mouseSensitivity   = 0.01; // Control Speed of rotations 
    int   selectedShapeIndex = 0;    // Index of shapes in the world array

    raylib::Vector3 movementDelta{0,0,0}; 
    raylib::Vector3 rotationDelta{0,0,0}; 

    void handleInput();         // Decide if an action is needed
    void update(World &world);  // Perform the needed action
};