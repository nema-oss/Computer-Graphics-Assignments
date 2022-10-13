#ifndef DVA338_LAB3_TRIANGLE_H
#define DVA338_LAB3_TRIANGLE_H
#include "Vec3.h"
#include "Ray.h"
#include "Surface.h"

class Triangle : public Surface{
public:
    Vec3f v0, v1, v2, normal;
public:
    Triangle() = default;
    Triangle(Vec3f vertex0, Vec3f vertex1, Vec3f vertex2): v0(vertex0), v1(vertex1), v2(vertex2){};
    Triangle(Vec3f vertex0, Vec3f vertex1, Vec3f vertex2, Vec3f & ambient, Vec3f & diffuse, Vec3f & specular, float alfa, float reflective) : v0(vertex0), v1(vertex1), v2(vertex2),
                                                                                                                            Surface(
                                                                                                                                    ambient,
                                                                                                                                    diffuse,
                                                                                                                                    specular,
                                                                                                                                    alfa,
                                                                                                                                    reflective) {};
    Triangle(Vec3f vertex0, Vec3f vertex1, Vec3f vertex2, Vec3f & ambient, Vec3f & diffuse, Vec3f & specular, float alfa, float refractiveness, float reflective) : v0(vertex0), v1(vertex1), v2(vertex2),
                                                                                                                                                  Surface(
                                                                                                                                                          ambient,
                                                                                                                                                          diffuse,
                                                                                                                                                          specular,
                                                                                                                                                          alfa,
                                                                                                                                                          refractiveness,
                                                                                                                                                          reflective) {};
    bool hit(const Ray & r, HitRec & rec, int * count) override;
    void computeSurfaceHitFields(const Ray & r, HitRec & rec) const override;
    Ray computeRefractionRay(Ray ray, HitRec hitRec, int *count) override;
    void computeNormal();
    bool noSelfReflection(Ray ray, HitRec hitRec) override;
};
#endif //DVA338_LAB3_TRIANGLE_H
