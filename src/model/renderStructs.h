#pragma once
#include "camera.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep

#include <vector>

class RenderEdge
{
  public:
    raylib::Vector3 a;
    raylib::Vector3 b;
    raylib::Color   color = raylib::GREEN;
};

class RenderShape
{
  public:
    std::vector<RenderEdge> edges;

    raylib::Vector3 position = {0, 0, 0};
    raylib::Vector3 rotation = {0, 0, 0};
    raylib::Vector3 scaling  = {0, 0, 0};
};

class RenderWorld
{
  public:
    MyCamera camera;
    std::vector<RenderShape> shapes;
};