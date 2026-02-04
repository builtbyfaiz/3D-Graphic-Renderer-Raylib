#pragma once
#include "raylib-cpp.hpp"
#include "vector3D.h"
#include <vector>

class Shape
{
  private:
    class EdgeIndexPair
    {
      private:
        raylib::Color color = raylib::GREEN;

      public:
        int first;
        int second;

        raylib::Color getColor();
        void setColor(raylib::Color c);

        EdgeIndexPair(int f, int s) : first(f), second(s) {}
    };

  public:
    std::vector<Vec3>          vertices;  // Points of a shape
    std::vector<EdgeIndexPair> edges;     // Index pair of vertices that make an Edge

    Vec3 position = {0, 0, 0}; // Position of shape in 3D space
    Vec3 rotation = {0, 0, 0}; // Rotation of shape in radians in 3D space

    void move(const Vec3 &delta);
    void rotate(const Vec3 &delta);
    void setColor(raylib::Color color);
};
