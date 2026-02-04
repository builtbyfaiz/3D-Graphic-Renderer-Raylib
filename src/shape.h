#pragma once
#include "raylib-cpp.hpp"
#include <vector>

class EdgeIndexPair
{
  public:
    int first;
    int second;

    raylib::Color color;

    void setColor(Color c);
    EdgeIndexPair(int f, int s, raylib::Color c = raylib::GREEN)
        : first(f), second(s), color(c) {}
};

class Shape
{
  public:
    std::vector<raylib::Vector3> vertices;           // Points of a shape
    std::vector<EdgeIndexPair>   edges;              // Index pair of vertices that make an Edge
    raylib::Vector3              position{0, 0, 0};  // Position of shape in 3D space
    raylib::Vector3              rotation{0, 0, 0};  // Rotation of shape in radians in 3D space

    void move(const raylib::Vector3 &delta);
    void rotate(const raylib::Vector3 &delta);
};
