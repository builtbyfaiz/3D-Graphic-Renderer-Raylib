#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep
#include "model/world.h"

// handles input, camera movement, shape movement
class Controller
{
  public:
    static bool moveMode; // Move camera, or individual shapes
    static int  moveSpeed; 
    static int  selectedShapeIndex; // Index of shapes in the world array

    static Vec3 camMove;
    static Vec3 shapeMove;

    static void handleInput();        // Decide if an action is needed
    static void update(World &world); // Perform the needed action
};