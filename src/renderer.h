#pragma once

#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

class Renderer
{
  public:
    static float focal;

    static Point2D transformCartesian(
        Point2D
            p); // Convert point to cartesian plane, so projection is accurate

    static Point2D convert2D(Point3D &p); // Project 3d Point to 2d screen

    static void render(Point3D p3D); // Renders 3d point on screen's cartesian plane

    Renderer();
};
