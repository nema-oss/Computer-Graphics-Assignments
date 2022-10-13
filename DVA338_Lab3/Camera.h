#ifndef DVA338_LAB3_CAMERA_H
#define DVA338_LAB3_CAMERA_H
#include "Vec3.h"
class Camera{
public:
    Vec3f position;
    float fov{};
public:
    Camera()= default;
    Camera(Vec3f & p, const float f) : position(p), fov(f){};

    void setPosition(Vec3f newPosition){
        position.x = newPosition.x;
        position.y = newPosition.y;
        position.z = newPosition.z;
    }

    void augmentX(float dx){position.x+=dx;}
    void augmentY(float dy){position.y+=dy;}
    void augmentZ(float dz){position.z+=dz;}
};

#endif //DVA338_LAB3_CAMERA_H
