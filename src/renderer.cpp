#include "renderer.h"
#include "constants.h"
#include "points.h"
#include "raylib-cpp.hpp"

/*
- Inverts Y axis around the origin
- Centers origin on 0,0
- Returns translated 2D point
*/
Point2D Renderer::transformCartesian(Point2D p)
{
    p.y = -p.y;
    p.x += (GetScreenWidth() - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;

    return {p.x, p.y};
}

// Project the 3d Point onto the 2d screen, Return projected point
Point2D Renderer::convert2D(Point3D &p)
{
    p.z = p.z == 0 ? 1 : p.z;
    float x = p.x / p.z;
    float y = p.y / p.z;
    return {x, y};
}

/*
- Converts 3D point to 2D, transforms to cartesian plane and draws it on screen
*/
void Renderer::render(Point3D p3D)
{
    Point2D p2D = convert2D(p3D);       // Convert from 3d to 2d
    p2D = transformCartesian(p2D);      // Translate to cartesian plane
    p2D = {round(p2D.x), round(p2D.y)}; // Clean of floating point errors

    DrawRectangle(p2D.x, p2D.y, POINT_SIZE, POINT_SIZE,
                  RED); // Render to screen
}



