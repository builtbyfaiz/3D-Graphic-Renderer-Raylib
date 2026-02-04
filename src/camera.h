#pragma once
#include "raylib-cpp.hpp"

struct MyCamera
{
    raylib::Vector3 position{0,0,0};
    raylib::Vector3 rotation{0,0,0};
    float focal = 600.0f;

    void move(const raylib::Vector3 &delta);
    void rotate(const raylib::Vector3 &delta);
};