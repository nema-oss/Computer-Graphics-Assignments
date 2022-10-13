#ifndef DVA338_LAB3_LIGHT_H
#define DVA338_LAB3_LIGHT_H
#include "Vec3.h"

class Light{
public:

    Vec3f position;
    Vec3f Ia, Id, Is;
public:
    Light()=default;
    Light(Vec3f p, Vec3f ambient, Vec3f diffuse, Vec3f specular) : position(p), Ia(ambient), Id(diffuse), Is(specular){};

};
#endif //DVA338_LAB3_LIGHT_H
