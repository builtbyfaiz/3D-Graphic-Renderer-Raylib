#pragma once

#include "globals.h"
#include "raylib-cpp.hpp"
#include "world.h"

// clang-format off
class Renderer
{
  public:
    static float focal;

    static void transformPoint(raylib::Vector3 &p);          // Convert point to cartesian plane, so projection is accurate
    static void projectPoint(raylib::Vector3 &p);            // Project 3D Point on 2d screen
    static void preparePoint(raylib::Vector3 &p);            // Transforms and projects a 3D point
    static void drawPoint(raylib::Vector3 &p, Color color);  // Renders point on 2d screen's cartesian plane
    
    static void transformShape(Shape &shape);  // Rotate, Scale, Translate shape in 3D space
    static void projectShape(Shape &shape);    // Project 3D shape on 2D screen's cartesian plane
    static void drawShape(Shape &shape);       // Renders 3D shape on 2D screen's cartesian plane
    
    static void transformWorld(World &world);  // Rotate, Scale, Translate shapes of world in 3D space
    static void projectWorld(World &world);    // Project 3D world to 2D screen's cartesian plane
    static void prepareWorld(World &world);    // Transforms and projects all shapes inside a world
    static void drawWorld(World &world);       // Renders 3D world on 2D screen's cartesian plane

    static void render(World &world);  // Render world via render pipeline, Transform->Project->Draw
    
    // TEMP DEBUG FUCTION
    static void pushWorldIntoView(World &world, int amount);

    // clang-format on
};
