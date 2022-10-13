#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Vec3.h"
#include "Ray.h"
#include "Surface.h"

class Sphere : public Surface {
public:
	Vec3f c;
	float r;
public:
	Sphere(const Vec3f & cen, float rad) : c(cen), r(rad){ };
    Sphere(const Vec3f & cen, float rad, Vec3f & ambient, Vec3f & diffuse, Vec3f & specular, float alfa, float reflectiveness): c(cen), r(rad),
                                                                                                          Surface(
                                                                                                                  ambient,
                                                                                                                  diffuse,
                                                                                                                  specular,
                                                                                                                  alfa,
                                                                                                                  reflectiveness) {};
    Sphere(const Vec3f & cen, float rad, Vec3f & ambient, Vec3f & diffuse, Vec3f & specular, float alfa, float refractiveness, float reflectiveness) : c(cen), r(rad),
                                                                                                                                 Surface(
                                                                                                                                         ambient,
                                                                                                                                         diffuse,
                                                                                                                                         specular,
                                                                                                                                         alfa,
                                                                                                                                         refractiveness,
                                                                                                                                         reflectiveness) {};
	bool hit(const Ray & r, HitRec & rec, int * count) override;
	void computeSurfaceHitFields(const Ray & r, HitRec & rec) const override;
    Ray computeRefractionRay(Ray ray, HitRec hitRec, int *count) override;
    bool noSelfReflection(Ray ray, HitRec hitRec) override;

};

#endif