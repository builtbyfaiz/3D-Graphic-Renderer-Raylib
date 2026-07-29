#pragma once
#include "model/world.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep

// handles input, camera movement, shape movement
class Controller
{
  private:
    enum class ControlMode
    {
        Cam,
        Shape
    } controlMode{ControlMode::Cam};

    float moveSpeed          = 2;      // Control Speed of movement
    float mouseSensitivity   = 0.01;   // Control Speed of rotations
    int   selectedShapeIndex = 0;      // Index of shapes in the world array
    bool  rotationMode       = false;  // Toggle rotation
    
    float pitch, yaw, roll; // Vars for rotatons

    raylib::Vector3 movementDelta{0, 0, 0};
    raylib::Vector3 rotationDelta{0, 0, 0};

    void toggleControlMode();   // Decide if to move camera or shapes
    void toggleRotationMode();  // Decide if to move camera or shapes

  public:
    void handleInput();        // Decide if an action is needed
    void update(World &world); // Perform the needed action
};