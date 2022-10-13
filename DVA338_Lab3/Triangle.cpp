#include "Vec3.h"
#include "Ray.h"
#include "Triangle.h"
//Möller–Trumbore ray-triangle intersection algorithm: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
 bool Triangle::hit(const Ray &r, HitRec &rec, int *count){
    *(count) = *(count) + 1;
     const float EPSILON = 0.0000001;
     Vec3f edge1, edge2, h, s, q;
     float a,f,u,v;
     edge1 = v1 - v0;
     edge2 = v2 - v0;
     h = r.d.cross(edge2);
     a = edge1.dot(h);
     if (a > -EPSILON && a < EPSILON) {
         return false;    // ray is parallel to triangle
     }
     f = 1.0f/a;
     s = r.o - v0;
     u = f * s.dot(h);
     if (u < 0.0 || u > 1.0) {
         return false;
     }
     q = s.cross(edge1);
     v = f * r.d.dot(q);
     if (v < 0.0 || u + v > 1.0) {
         return false;
     }

     float t = f * edge2.dot(q);
     if (t > EPSILON){ // ray intersection
             rec.tHit = t;
             rec.anyHit = true;
             rec.surfaceHit = TRIANGLE;
             return true;
     }
     else //there is a line intersection but not a ray intersection
         return false;
}

void Triangle::computeSurfaceHitFields(const Ray &r, HitRec &rec) const {
    rec.p = r.o + r.d * rec.tHit;
    rec.n = this->normal;
}

void Triangle::computeNormal() {
    Vec3f U = v1-v0;
    Vec3f V = v2-v0;
    this->normal = U.cross(V).normalize();
}

Ray Triangle::computeRefractionRay(Ray ray, HitRec hitRec, int *count) {
    Ray refractionRay;
    refractionRay.d = getRefractionRayDirection(ray, hitRec, false);
    refractionRay.o = hitRec.p;
    return refractionRay;
}

bool Triangle::noSelfReflection(Ray ray, HitRec hitRec) {
    return true;
}

