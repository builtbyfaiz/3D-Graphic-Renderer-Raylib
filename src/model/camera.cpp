#include "camera.h"


void MyCamera::move(const raylib::Vector3 &movementDelta) 
{
    // position += movementDelta;
    Matrix matrix = MatrixRotateXYZ(rotation);
    position += Vector3Transform(movementDelta, matrix);

}

void MyCamera::rotate(const raylib::Vector3 &delta) 
{
    rotation += delta;
}