#include "shape.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep
#include "vector3D.h"
#include <fstream>
#include <iostream>
#include <string>

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

void Shape::setColor(raylib::Color color)
{
    for (auto &edge : edges)
    {
        edge.setColor(color);
    }
}

// Saves shape as a text file in the given path, Default mode: override
void Shape::saveShape(std::string filePath)
{
    std::ofstream ofile(filePath);

    if (!ofile.is_open())
    {
        std::cout << "Save failed, Failed to open " << filePath + "\n";
        return;
    }

    ofile << "VERTICES " << vertices.size() << "\n";
    for (const auto &point : vertices)
    {
        ofile << point.x << " " << point.y << " " << point.z << "\n";
    }

    ofile << "EDGES " << edges.size() << "\n";
    for (const auto &edge : edges)
    {
        ofile << edge.first << " " << edge.second << " ";

        ofile << (int)edge.color.GetR() << " " << (int)edge.color.GetG() << " "
              << (int)edge.color.GetB() << " " << (int)edge.color.GetA()
              << "\n";
    }

    ofile << "TRANSFORM\n";
    ofile << position.x << " " << position.y << " " << position.z << "\n";
    ofile << rotation.x << " " << rotation.y << " " << rotation.z << "\n";
}

// Loads itself from a text file at the given path.
void Shape::loadShape(std::string filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cout << "Load failed, Failed to open " << filePath + "\n";
        return;
    }

    vertices.clear();
    edges.clear();

    std::string label;
    int count;
    
    // Vertices
    file >> label >> count; 
    if (label != "VERTICES") // "VERTICES N"
    {
        std::cout << "Invalid format (VERTICES)\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        Vec3 v;
        file >> v.x >> v.y >> v.z;
        vertices.push_back(v);
    }

    // Edges
    file >> label >> count; // "EDGES N"
    if (label != "EDGES")
    {
        std::cout << "Invalid format (EDGES)\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        EdgeIndexPair edge(0, 0);

        int r, g, b, a;

        file >> edge.first >> edge.second >> r >> g >> b >> a;

        edge.setColor(raylib::Color(r, g, b, a));

        edges.push_back(edge);
    }

    // Transformations
    file >> label; // "TRANSFORM"
    if (label != "TRANSFORM")
    {
        std::cout << "Invalid format (TRANSFORM)\n";
        return;
    }

    file >> position.x >> position.y >> position.z;
    file >> rotation.x >> rotation.y >> rotation.z;
}

// Getter, Setter
void          Shape::EdgeIndexPair::setColor(raylib::Color c) { this-> color = c; }
raylib::Color Shape::EdgeIndexPair::getColor()                { return color; }
