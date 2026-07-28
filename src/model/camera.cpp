#include "camera.h"


void MyCamera::move(const raylib::Vector3 &delta) 
{
    position += delta;
}

void MyCamera::rotate(const raylib::Vector3 &delta) 
{
    rotation += delta;
}