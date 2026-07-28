#pragma once
#include "raylib-cpp.hpp" // IWYU pragma: keep
#include "vector3D.h"

struct MyCamera
{
    Vec3 position{0,0,0};
    Vec3 rotation{0,0,0};
    float focal = 600.0f;

    void move(const Vec3 &delta);
    void rotate(const Vec3 &delta);
};