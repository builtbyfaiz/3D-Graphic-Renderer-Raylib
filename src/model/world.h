#pragma once
#include "camera.h"
#include "shape.h"

class World
{
  public:
    std::vector<Shape> shapes;
    MyCamera camera;
};