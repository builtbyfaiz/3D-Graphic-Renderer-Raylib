#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep

#include "model/world.h"
#include "model/renderStructs.h"

class Renderer
{
  private:
    RenderWorld renderWorld;

    float focal = 500.f;
    
    void projectPoint(raylib::Vector3 &p); // Project 3D Point on 2d screen
    void  toCartesian(raylib::Vector3 &p); // Convert point to cartesian plane, so projection is accurate
    
    void transformEdge(RenderEdge &edge, 
                       const raylib::Vector3 &scaling,
                       const raylib::Vector3 &position,
                       const raylib::Matrix  &rotation);

    void projectEdge(RenderEdge &edge);

    void transformShape(RenderShape &shape); // Rotate, Scale, Translate shape in 3D space
    void projectShape(RenderShape &shape);   // Project 3D shape on 2D screen's cartesian plane
    void drawShape(RenderShape &shape);      // Renders 3D shape on 2D screen's cartesian plane

    void clipWorld();          // Keep only objects in front of camera visible
    void transformWorld();     // Rotate, Scale, Translate shapes of world in 3D space
    void projectWorld();       // Project 3D world to 2D screen's cartesian plane
    void drawWorld();          // Renders 3D world on 2D screen's cartesian plane

    RenderShape createRenderShape(const Shape &shape);
    void prepareRenderWorld(const World &meshWorld); // Applies transformations to and returns render copy of world

    raylib::Color applyDepth(raylib::Color c, float depth); // Provides faded colors to edges based on depth
    void drawPoint(raylib::Vector3 &p, Color color); // Renders point on 2d screen's cartesian plane

  public:
    void render(World &meshWorld); // Render world via render pipeline, Transform->Project->Draw
    void pushWorldIntoView(int amount); // TEMP DEBUG FUCTION
};
