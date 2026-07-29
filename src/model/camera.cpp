#include "camera.h"


void MyCamera::move(const raylib::Vector3 &movementDelta) 
{
    position += movementDelta;

}

void MyCamera::rotate(const raylib::Vector3 &rotationDelta) 
{
    rotation += rotationDelta;
}