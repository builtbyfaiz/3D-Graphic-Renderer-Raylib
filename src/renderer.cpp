#include "renderer.h"
#include "globals.h"
#include "points.h"
#include "raylib-cpp.hpp"

/*
- Inverts Y axis around the origin
- Centers origin on 0,0
- Returns translated 2D point
*/
Point2D Renderer::transformCartesian(Point2D &p)
{
    p.y = -p.y;
    p.x += (GetScreenWidth() - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;

    return {p.x, p.y};
}

/* 
- Project the 3D Point onto the 2D screen
- Return projected 2D point
*/
Point2D Renderer::project(Point3D &p)
{
    p.z = p.z == 0 ? 1 : p.z;

    float x = p.x / p.z * focal;
    float y = p.y / p.z * focal;

    return {x, y};
}

/*
- Converts 3D point to 2D
- Transforms to cartesian plane
- Draws the points and their connections/edges on screen
*/
void Renderer::renderShape(Shape &shape, Connections &connections)
{
    // clang-format off
    for (auto &edge : connections)
    {
        Point3D A3D = shape[edge.first];  // first point
        Point3D B3D = shape[edge.second]; // second point
        
        // Prepare points for rendering
        Point2D A2D = preparePoint(A3D);
        Point2D B2D = preparePoint(B3D);

        // Render points
        // renderPoint(A2D,RED);
        // renderPoint(B2D,RED);
        
        // Render Edge
        DrawLine(A2D.x+(POINT_SIZE/2), A2D.y+(POINT_SIZE/2), B2D.x+(POINT_SIZE/2), B2D.y+(POINT_SIZE/2), BLUE); 
    }
    // clang-format on
}

/*
- Projects 3D point to 2D
- Transforms to cartesian plane
- Returns prepared 2D point for rendering
*/
Point2D Renderer::preparePoint(Point3D &p3D)
{
    // clang-format off
    Point2D p2D = project(p3D);                  // Convert from 3D to 2D
            p2D = transformCartesian(p2D);       // Translate to cartesiasn plane
            p2D = {round(p2D.x), round(p2D.y)};  // Fix floating point errors

    return p2D;
    // clang-format on
}

// Render the 2D point on screen in given Color
void Renderer::renderPoint(Point2D &p, Color color)
{
    raylib::Rectangle rect = {
        p.x, p.y, POINT_SIZE,
        POINT_SIZE};  // Turn point into renderable rectangles with size
    rect.Draw(color); // Render to screen
}

void Renderer::moveShape(Shape &shape, float dx, float dy)
{
    for (auto &point : shape)
    {
        point.x += dx;
        point.y += dy;
    }
}

void Renderer::handleInput(Shape &shape)
{
    if (GetKeyPressed() == 0) return; // Return if no key pressed
    
    // Decide change in x or y based on input
    if (IsKeyDown(KEY_W)) dy += 1;
    if (IsKeyDown(KEY_S)) dy -= 1;
    if (IsKeyDown(KEY_A)) dx -= 1;
    if (IsKeyDown(KEY_D)) dx += 1;
    
    if (dx != 0 || dy != 0)
    {
        Renderer::moveShape(shape, dx, dy);
    }
}

float Renderer::focal = 300.f;
int   Renderer::dx    = 0;
int   Renderer::dy    = 0;
