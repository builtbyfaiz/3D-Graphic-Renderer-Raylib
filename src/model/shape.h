#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep

#include <vector>

class Shape
{
  public:

    class EdgeIndexPair
    {
      public:
        int first;
        int second;
        raylib::Color color = raylib::GREEN;

        raylib::Color getColor();
        void setColor(raylib::Color c);
        
        EdgeIndexPair(){}
        EdgeIndexPair(int f, int s) : first(f), second(s) {}
    };

    std::vector<raylib::Vector3> vertices; // Points of a shape
    std::vector<EdgeIndexPair>   edges;    // Index pairs of vertices that join to make edge of the shape

    raylib::Vector3 position = {0, 0, 0};  // Position of shape in 3D space
    raylib::Vector3 rotation = {0, 0, 0};  // Rotation of shape in radians in 3D space
    raylib::Vector3 scaling  = {0, 0, 0};  // Scale of shape in radians in 3D space

    void move(const raylib::Vector3 &delta);    // Moves the shape by a 3D vector
    void scale(const raylib::Vector3 &delta);   // Moves the shape by a 3D vector
    void rotate(const raylib::Vector3 &delta);  // Rotates the shape by a 3D vector
    void setColor(const raylib::Color color);   // Sets Color of the shape

    void saveShape(std::string filePath);  // Stores Shape to a raw text file
    void loadShape(std::string filePath);  // Loads Shape from a raw text file

    Shape() = default;
    Shape(std::string filePath) { loadShape(filePath); }
};
