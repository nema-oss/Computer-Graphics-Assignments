#ifndef DVA338_LAB3_TRIANGLELIGHT_H
#define DVA338_LAB3_TRIANGLELIGHT_H

#include "Light.h"
#include "Triangle.h"

class TriangleLight : public Triangle{
public:
    Light * lights;
    int numberOfLights;
public:
    TriangleLight() = default;
    TriangleLight(Vec3f v0, Vec3f v1, Vec3f v2, int density, Vec3f ambient, Vec3f diffuse, Vec3f specular) : Triangle(v0,v1,v2){
        numberOfLights = density*density;
        lights = (Light *) malloc (sizeof(Light)*numberOfLights);
        Vec3f position = v0, target = v1;
        Vec3f downDirection = v1-v0;
        downDirection = downDirection * (1.0f/float(density+1));
        Vec3f rightDirection = v2-v1;
        rightDirection = rightDirection * (1.0f/float(density+1));
        for(int i=0; i<density; i++){ //using the same approach used for the geometry fur shader
            for(int j=0; j<density; j++){
                position+=downDirection;
                *(lights+i*density+j) = Light(position, ambient, diffuse, specular);
            }
            position=v0;
            target = target + rightDirection;
            downDirection = target - position;
        }
    }

};
#endif
