
#include "renderer.h"

#include "globals.h"
#include "model/camera.h"
#include "raylib-cpp.hpp" // IWYU pragma: keep

// #TODO turn this into Compute renderer, not Destructive

// clang-format off
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
}

// Render the 2D point on screen in given Color
void Renderer::drawPoint(raylib::Vector3 &p, Color color)
{
    // Turn point into renderable rectangles with size
    raylib::Rectangle rect = {p.x, p.y, POINT_SIZE, POINT_SIZE};  
    rect.Draw(color); 
}

/*
- Inverts Y axis around the origin
- Centers origin on 0,0
*/
void Renderer::toCartesian(raylib::Vector3 &p)
{
    p.y  = -p.y;
    p.x += (GetScreenWidth()  - POINT_SIZE) / 2;
    p.y += (GetScreenHeight() - POINT_SIZE) / 2;
}

void Renderer::transformEdge(RenderEdge &edge, 
                            const raylib::Vector3 &scaling,
                            const raylib::Vector3 &position,
                            const raylib:: Matrix &rotation)
{
    edge.a *= scaling;
    edge.a  = Vector3Transform(edge.a, rotation);
    edge.a += position;

    edge.b *= scaling;
    edge.b  = Vector3Transform(edge.b, rotation);
    edge.b += position;
}


void Renderer::projectEdge(RenderEdge &edge)
{
    projectPoint(edge.a);  // Convert from 3D to 2D
    projectPoint(edge.b);  
    
    toCartesian (edge.a);  // Translate to cartesian plane
    toCartesian (edge.b);  
}

// - Transform = {scale, translate, rotate} shape to its accurate position
void Renderer::transformShape(RenderShape &shape)
{
    Matrix rotation = MatrixRotateXYZ(shape.rotation);

    for (auto &edge : shape.edges)
        transformEdge(edge, shape.scaling, shape.position, rotation);   
}

void Renderer::projectShape(RenderShape &shape)
{
    for (auto &edge : shape.edges)
        projectEdge(edge);
}

/*
- Draws the points or their connections/edges on screen
*/
void Renderer::drawShape(RenderShape &shape)
{
    for (auto &edge : shape.edges)
    {
        float depth = (edge.a.z + edge.b.z) * 0.5f;

        DrawLine(
            edge.a.x, edge.a.y,
            edge.b.x, edge.b.y,
            applyDepth(edge.color, depth)
        );
    }
}

void Renderer::transformWorld()
{
    for (auto &shape : renderWorld.shapes)
    {
        // Minus Camera's Position to make it the origin
        shape.position -= renderWorld.camera.position; 
        transformShape(shape);

        // Adjust Shape's rotation relative to the camera
        raylib::Vector3 camRotation= renderWorld.camera.rotation;
        Matrix rotation = MatrixRotateXYZ({camRotation.x, camRotation.y, camRotation.z});

        for (auto &edge : shape.edges) {
            edge.a = Vector3Transform(edge.a, rotation);
            edge.b = Vector3Transform(edge.b, rotation);

        }
    }
}

void Renderer::clipWorld()
{
    float nearPlane = 1.0f;

    for (auto &shape : renderWorld.shapes)
    {
        std::vector<RenderEdge> visibleEdges;
        // visibleEdges.reserve(shape.edges.size());

        for (auto edge : shape.edges)
        {
            bool aBehind = edge.a.z < nearPlane;
            bool bBehind = edge.b.z < nearPlane;

            if (aBehind && bBehind) // Edge is behind camera, mark it invisible
                continue;

            if (aBehind || bBehind) // Edge is partially behind, Clip Edge 
            {
                float ratio = (nearPlane - edge.a.z) / (edge.b.z - edge.a.z); // Normalization 0-1
                raylib::Vector3 pointI = edge.a + (edge.b - edge.a) * ratio;  // Intersection Point

                if (aBehind) edge.a = pointI;
                if (bBehind) edge.b = pointI;
            }

            visibleEdges.push_back(edge);
        }

        shape.edges = visibleEdges;
    }
}

void Renderer::projectWorld()
{
    for (auto &shape : renderWorld.shapes)
    {
        projectShape(shape);
    }
}

// Draw given world to screen
void Renderer::drawWorld() 
{
    BeginDrawing();
    ClearBackground(BLACK);

    for(auto &shape: renderWorld.shapes) 
    {
        drawShape(shape);
    }

    EndDrawing();
}

void Renderer::pushWorldIntoView(int amount)
{
    for (auto &shape : renderWorld.shapes)
    {
        for (auto &edge : shape.edges)
        {
            edge.a.z += amount;
            edge.b.z += amount;
        }
    }
}

void Renderer::prepareRenderWorld(const World &meshWorld)
{
    renderWorld.camera = meshWorld.camera;
    renderWorld.shapes.clear();

    // Convert Mesh into Render World
    for (const auto &shape : meshWorld.shapes)
    {
        RenderShape renderShape = createRenderShape(shape);
        renderWorld.shapes.push_back(renderShape);
    }

    transformWorld();  // Transform
    clipWorld     ();  // Clip World #TODO, temporary, add proper clipping at a shape level
    projectWorld  ();  // Project 3D to 2D
}

RenderShape Renderer::createRenderShape(const Shape &shape)
{
    RenderShape renderShape;
    renderShape.position = shape.position;
    renderShape.rotation = shape.rotation;
    renderShape.scaling  = shape.scaling;

    for (const auto &edge : shape.edges)
    {
        // Convert vertices via indices to edges containing 3D points
        RenderEdge renderEdge;
        renderEdge.a     = shape.vertices[edge.first];
        renderEdge.b     = shape.vertices[edge.second];
        renderEdge.color = edge.color;

        renderShape.edges.push_back(renderEdge);
    }
    return renderShape;
}


/*
Returns a faded color based on average depth of the edge
- Has a start value
- Lasts over a range
- Uses Color Alpha to provide depth illusion
*/
raylib::Color Renderer::applyDepth(raylib::Color color, float depth)
{
    float fadeStart = 400.0f;
    float fadeRange = 1000.0f;

    float fade = Clamp((depth - fadeStart) / fadeRange, 0.0f, 1.0f);

    fade = fade * fade * (3.0f - 2.0f * fade);

    color.a = (unsigned char)(255 * (1.0f - fade));

    return color;
}

// Render world via render pipeline, Transform->Project->Draw
void Renderer::render(World &meshWorld)
{
    prepareRenderWorld(meshWorld);
    drawWorld();
}