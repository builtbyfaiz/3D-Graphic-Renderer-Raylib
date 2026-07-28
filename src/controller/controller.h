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

    float controlSpeed       = 1.5; // Control Speed of rotations and movement
    int   selectedShapeIndex = 0;   // Index of shapes in the world array

    raylib::Vector3 movementDelta{0,0,0}; 

    void handleInput();         // Decide if an action is needed
    void update(World &world);  // Perform the needed action
};