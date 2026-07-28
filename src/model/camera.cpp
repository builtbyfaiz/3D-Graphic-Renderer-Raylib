#include "camera.h"
#include "vector3D.h"

void MyCamera::move(const Vec3 &delta) 
{
    position.x += delta.x;
    position.y += delta.y;
    position.z += delta.z;
}

void MyCamera::rotate(const Vec3 &delta) 
{
    rotation.x += delta.x;
    rotation.y += delta.y;
    rotation.z += delta.z;
}