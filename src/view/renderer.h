#pragma once
#include "model/world.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep

class Renderer
{
  private:
    float focal = 500.f;
    
    void toCartesian(raylib::Vector3 &p);             // Convert point to cartesian plane, so projection is accurate
    void projectPoint(raylib::Vector3 &p);            // Project 3D Point on 2d screen
    void preparePoint(raylib::Vector3 &p);            // Convert to cartesian and projects a 3D point
    void drawPoint(raylib::Vector3 &p, Color color);  // Renders point on 2d screen's cartesian plane
    
    void applyRotation(Shape &shape);     // Rotate shape in 3D space

    void transformShape(Shape &shape); // Rotate, Scale, Translate shape in 3D space
    void projectShape(Shape &shape);   // Project 3D shape on 2D screen's cartesian plane
    void drawShape(Shape &shape);      // Renders 3D shape on 2D screen's cartesian plane

    void transformWorld(World &world); // Rotate, Scale, Translate shapes of world in 3D space
    void projectWorld(World &world);   // Project 3D world to 2D screen's cartesian plane
    void drawWorld(World &world);      // Renders 3D world on 2D screen's cartesian plane

  public:
    void render(World &world); // Render world via render pipeline, Transform->Project->Draw
    void pushWorldIntoView(World &world, int amount); // TEMP DEBUG FUCTION
};
