#include "raylib-cpp.hpp"
#include "world.h"
// handles input, camera movement, shape movement
class Controller 
{
    public:
    static bool moveMode;

    static raylib::Vector3 camMove;
    static int moveSpeed;
    static raylib::Vector3 shapeMove;

    static void handleInput();         // Decide if an action is needed
    static void update(World &world);  // Perform the needed action
};