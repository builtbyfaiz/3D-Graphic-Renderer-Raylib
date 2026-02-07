#include "raylib-cpp.hpp"

using namespace std;

class Point2D
{
  public:
    float x, y;
};

class Point3D
{
  public:
    float x, y, z;
    int size;

    Point3D(int x, int y, int z) : x(x), y(y), z(z), size(20) {};
};

class Renderer
{
    public:
    static Point2D project2D(Point3D &p)
    {
        float x = p.x / p.z;
        float y = p.y / p.z;
        return {x, y};
    }
};

int main()
{
    raylib::Window graphicWindow(800, 600, "Graphic Render", FLAG_VSYNC_HINT);
    SetTargetFPS(75);

    Point3D p(20, 20, 20);
    Point2D pPrime = Renderer::project2D(p);
    while (!WindowShouldClose())
    {
        pPrime = Renderer::project2D(p);
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(pPrime.x, pPrime.y, 20,20, RED) ;
        EndDrawing();
    }
}
