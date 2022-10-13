#ifndef DVA338_LAB3_SURFACE_H
#define DVA338_LAB3_SURFACE_H
#include "Vec3.h"
#include "Ray.h"

class Surface {
public:
    int id;
    Vec3f ka, kd, ks;
    float shininess;
    float reflectiveNess, refractiveIndex;
    bool isTransparent=false;
public:
    Surface() = default;
    Surface(Vec3f &ambient, Vec3f &diffuse, Vec3f &specular, float alfa, float reflectiveness)
            : ka(ambient), kd(diffuse), ks(specular), shininess(alfa), refractiveIndex(), reflectiveNess(reflectiveness){};
    Surface(Vec3f &ambient, Vec3f &diffuse, Vec3f &specular, float alfa, float refractiveness, float reflectiveness)
            : ka(ambient), kd(diffuse), ks(specular), shininess(alfa), refractiveIndex(refractiveness), reflectiveNess(reflectiveness){};

    Vec3f getRefractionRayDirection(Ray & r, HitRec & hitRec, bool inside) const;

    virtual bool hit(const Ray &r, HitRec &rec, int *count) ;
    virtual void computeSurfaceHitFields(const Ray & r, HitRec & rec) const ;
    virtual Ray computeRefractionRay(Ray ray, HitRec hitRec, int *count);
    virtual bool noSelfReflection(Ray ray, HitRec hitRec);
};
#endif //DVA338_LAB3_SURFACE_H
