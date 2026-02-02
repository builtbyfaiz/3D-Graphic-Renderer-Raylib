#pragma once
#include "globals.h"

class Point2D
{
  public:
    float x, y;
};

class Point3D
{
  public:
    float x, y, z;
    int size;

    Point3D(int x, int y, int z) : x(x), y(y), z(z), size(POINT_SIZE) {};
};