#include "camera.h"

void MyCamera::move(const raylib::Vector3 &delta) 
{
    position.x += delta.x;
    position.y += delta.y;
    position.z += delta.z;
}

void MyCamera::rotate(const raylib::Vector3 &delta) 
{
    rotation.x += delta.x;
    rotation.y += delta.y;
    rotation.z += delta.z;
}