#pragma once

#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

class Renderer
{
  public:
    static float focal;
    static int dx;
    static int dy;

    // clang-format off
    using Shape       = std::vector<Point3D>; // All points of the shape
    using Edge        = std::pair<int, int>;  // Indices of two Points to connect i.e Edge of shape
    using Connections = std::vector<Edge>;    // All connections of shape i.e All edges or All connections of points

    static Point2D project(Point3D &p3D);                          // Project 3d Point on 2d screen
    static Point2D transformCartesian(Point2D &p2D);               // Convert point to cartesian plane, so projection is accurate
    static Point2D preparePoint(Point3D &p3D);                     // Projects and transforms a 3D point

    static void renderShape(Shape &shape, Connections &connections); // Renders 3d shape on 2d screen's cartesian plane
    static void renderPoint(Point2D &p2D, Color color);            // Renders 3d point on 2d screen's cartesian plane

    static void moveShape(Shape &shape, float dx, float dy);        // Move shape by dx and dy
    static void handleInput(Shape &shape);
    // clang-format on
};
