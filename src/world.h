#pragma once
#include "shape.h"
#include "camera.h"

class World
{   
    public:
    std::vector<Shape> shapes;
    MyCamera camera;
};