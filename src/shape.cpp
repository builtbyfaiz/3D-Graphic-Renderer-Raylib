#include "vector3D.h"
#include "shape.h"
#include "raylib-cpp.hpp"

void Shape::move(const Vec3 &delta) 
{
    position.x += delta.x;
    position.y += delta.y;
    position.z += delta.z;
}

void Shape::rotate(const Vec3 &delta) 
{
    rotation.x += delta.x;
    rotation.y += delta.y;
    rotation.z += delta.z;
}

void Shape::setColor(raylib::Color color) {
    for (auto &edge : edges)
    {
        edge.setColor(color);
    }
    
}

// Getter, Setter
void          Shape::EdgeIndexPair::setColor(raylib::Color c) { this->color = c; }
raylib::Color Shape::EdgeIndexPair::getColor()                { return color; }
