#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep

#include <vector>

class Shape
{
  private:
    class EdgeIndexPair
    {   
      public:
      int first;
      int second;
      raylib::Color color = raylib::GREEN;

        raylib::Color getColor();
        void setColor(raylib::Color c);

        EdgeIndexPair(int f, int s) : first(f), second(s) {}
    };

  public:
    std::vector<raylib::Vector3> vertices;  // Points of a shape
    std::vector<EdgeIndexPair>   edges;     // Index pair of vertices that make an Edge

    raylib::Vector3 position = {0, 0, 0}; // Position of shape in 3D space
    raylib::Vector3 rotation = {0, 0, 0}; // Rotation of shape in radians in 3D space

    void move(const raylib::Vector3 &delta);
    void rotate(const raylib::Vector3 &delta);
    void setColor(raylib::Color color);
    void saveShape(std::string fileName);  // Stores Shape to a raw text file
    void loadShape(std::string fileName);  // Loads Shape from a raw text file
};
