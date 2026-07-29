
#include "renderer.h"

#include "globals.h"
#include "model/camera.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep

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
    p.z = p.z == 0 ? 0.001 : p.z;

    float x = p.x / p.z * focal;
    float y = p.y / p.z * focal;

    p.x = x; 
    p.y = y; 
    // p.z = 0; 
}

// Render the 2D point on screen in given Color
void Renderer::drawPoint(raylib::Vector3 &p, Color color)
{
    // Turn point into renderable rectangles with size
    raylib::Rectangle rect = {p.x, p.y, POINT_SIZE, POINT_SIZE};  
    rect.Draw(color); 
}

// - Rotate, Scale, Translate shape to its accurate position
void Renderer::transformShape(Shape &shape)
{
    Matrix rotation = MatrixRotateXYZ(shape.rotation);
    // Transform = {scale, translate, rotate}, project, render
    for (auto &point : shape.vertices)
    {
        point *= shape.scaling;                      // Scale
        point  = Vector3Transform(point, rotation);  // Rotation
        point += shape.position;                     // Move/Translate
    }
}

void Renderer::projectShape(Shape &shape)
{
    for (auto &point : shape.vertices)
    {
        projectPoint(point);  // Convert from 3D to 2D
        toCartesian (point);  // Translate to cartesian plane
    }
}

/*
Returns a faded color based on average depth of the edge
- Has a start value
- Lasts over a range
- Uses Color Alpha to provide depth illusion
*/
raylib::Color Renderer::applyDepth(raylib::Color color, float depth)
{
    float fadeStart = 600.0f;
    float fadeRange = 700.0f;

    float fade = Clamp((depth - fadeStart) / fadeRange, 0.0f, 1.0f);

    fade = fade * fade * (3.0f - 2.0f * fade);

    color.a = (unsigned char)(255 * (1.0f - fade));

    return color;
}

/*
- Draws the points or their connections/edges on screen
*/
void Renderer::drawShape(Shape &shape)
{
    for (auto &edge : shape.edges)
    {
        auto pointA = shape.vertices[edge.first];
        auto pointB = shape.vertices[edge.second];

        float depth = (pointA.z + pointB.z) * 0.5f;

        DrawLine(
            pointA.x, pointA.y,
            pointB.x, pointB.y,
            applyDepth(edge.getColor(), depth)
        );
    }
}

void Renderer::transformWorld(World &world)
{
    for (auto &shape : world.shapes)
    {
        // Adjust Shape's position relative to the camera to be then projected
        shape.position -= world.camera.position; 
        transformShape(shape);

        // Adjust Shape's rotation relative to the camera
        raylib::Vector3 rotation = world.camera.rotation;
        Matrix view = MatrixRotateXYZ({rotation.x, rotation.y, rotation.z});
        for (auto &p : shape.vertices)
            p = Vector3Transform(p, view);
    }
}

void Renderer::clipWorld(World &world)
{
    float nearPlane = 1.0f;

    for (auto &shape : world.shapes)
    {
        for (auto &edge : shape.edges)
        {
            auto &pointA = shape.vertices[edge.first];
            auto &pointB = shape.vertices[edge.second];

            // Skip Edge if it's behind camera
            if (pointA.z < nearPlane && pointB.z < nearPlane) continue;

            // Clip Edges
            if (pointA.z < nearPlane || pointB.z < nearPlane)
            {
                //Current - start / end - start, Normalization formula, bounds start and end to 0 and 1
                float ratio = (nearPlane - pointA.z) / (pointB.z - pointA.z);

                // Point of intersection with Z plane
                auto PointI = pointA + (pointB - pointA) * ratio;

                // Clip point A or B whichever is behind the camera.
                if (pointA.z < nearPlane)
                    pointA = PointI;
                else
                    pointB = PointI;
            }
        }
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
    clipWorld     (worldCopy); // Clip World #TODO, temporary, add proper clipping at a shape level
    projectWorld  (worldCopy); // Project 3D to 2D
    drawWorld     (worldCopy); // Draw to screen
}