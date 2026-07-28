
#include "renderer.h"
#include "globals.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep
#include "model/camera.h"

// #TODO turn this into Compute renderer, not Destructive

// clang-format off
/*
- Inverts Y axis around the origin
- Centers origin on 0,0
*/
void Renderer::toCartesian(raylib::Vector3 &p)
{
    p.y = -p.y;
    p.x += (GetScreenWidth()  - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;
}

/* 
- Project the 3D Point onto the 2D screen
*/
void Renderer::projectPoint(raylib::Vector3 &p)
{
    p.z = p.z == 0 ? 0.01 : p.z;

    float x = p.x / p.z * focal;
    float y = p.y / p.z * focal;

    p.x = x; 
    p.y = y; 
    // p.z = 0;
}

/*
- Projects 3D point to 2D
- Transforms to cartesian plane
*/
void Renderer::preparePoint(raylib::Vector3 &p)
{
    projectPoint(p);              // Convert from 3D to 2D
    toCartesian(p);            // Translate to cartesiasn plane
}

// Render the 2D point on screen in given Color
void Renderer::drawPoint(raylib::Vector3 &p, Color color)
{
    // Turn point into renderable rectangles with size
    raylib::Rectangle rect = {p.x, p.y, POINT_SIZE, POINT_SIZE};  
    rect.Draw(color); 
}

void Renderer::applyRotation(Shape &shape)
{
    
}

// - Rotate, Scale, Translate shape to its accurate position
void Renderer::transformShape(Shape &shape)
{
    // Transform = {scale,translate,rotate}, project, render
    for (auto &point : shape.vertices)
    {
        point *= shape.scaling;   // Scale
        // Rotate #TODO
        point += shape.position;  // Move/Translate
    }
}

void Renderer::projectShape(Shape &shape)
{
    for (auto &point : shape.vertices)
    {
        preparePoint(point);
    }
}

/*
- Draws the points or their connections/edges on screen
*/
void Renderer::drawShape(Shape &shape)
{
    for(auto &edge: shape.edges) 
    {
        raylib::Vector3 A = shape.vertices[edge.first]; 
        raylib::Vector3 B = shape.vertices[edge.second];
        DrawLine(A.x, A.y, B.x, B.y, edge.getColor());  // Render Edge
    }
}

void Renderer::transformWorld(World &world)
{
    for (auto &shape : world.shapes)
    {
        shape.position -= world.camera.position;
        transformShape(shape);
    }
}

void Renderer::projectWorld(World & world)
{
    for (auto &shape : world.shapes)
    {
        projectShape(shape);
    }
}

// Draw given world to screen
void Renderer::drawWorld(World &world) 
{
    BeginDrawing();
    ClearBackground(BLACK);

    for(auto &shape: world.shapes) 
    {
        drawShape(shape);
    }

    EndDrawing();
}

void Renderer::pushWorldIntoView(World &world, int amount)
{
    for (auto &shape : world.shapes)
    {
        for (auto &point : shape.vertices)
        {
            point.z += amount;
        }
    }
}

// Render world via render pipeline, Transform->Project->Draw
void Renderer::render(World &world)
{
    World worldCopy = world;   // Copy the original to not cause floating drift in original world
    
    transformWorld(worldCopy); // Transform
    projectWorld  (worldCopy); // Project 3D to 2D
    drawWorld     (worldCopy); // Draw to screen
}