#pragma once
#include "points.h"
#include "raylib-cpp.hpp"
#include "constants.h"

class Renderer
{
  public:
  
    // Convert point to cartesian plane so, formulas apply and projection is accurate
    static Point2D transformCartesian(Point2D p);

    // Project the 3d Point onto the 2d screen
    static Point2D convert2D(Point3D &p);

    // Renders 3d point on screen's cartesian plane
    static void render(Point3D p3D);
};
