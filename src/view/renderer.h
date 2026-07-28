#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep
#include "model/vector3D.h"
#include "model/world.h"

  // clang-format off
  // clang-format on
namespace Renderer
{
extern float focal;

void transformPoint(Vec3 &p);          // Convert point to cartesian plane, so projection is accurate
void projectPoint(Vec3 &p);            // Project 3D Point on 2d screen
void preparePoint(Vec3 &p);            // Transforms and projects a 3D point
void drawPoint(Vec3 &p, Color color);  // Renders point on 2d screen's cartesian plane

void transformShape(Shape &shape);  // Rotate, Scale, Translate shape in 3D space
void projectShape(Shape &shape);    // Project 3D shape on 2D screen's cartesian plane
void drawShape(Shape &shape);       // Renders 3D shape on 2D screen's cartesian plane

void transformWorld(World &world);  // Rotate, Scale, Translate shapes of world in 3D space
void projectWorld(World &world);    // Project 3D world to 2D screen's cartesian plane
void prepareWorld(World &world);    // Transforms and projects all shapes inside a world
void drawWorld(World &world);       // Renders 3D world on 2D screen's cartesian plane

void render(World &world);  // Render world via render pipeline, Transform->Project->Draw

  // TEMP DEBUG FUCTION
void pushWorldIntoView(World &world, int amount);
}
