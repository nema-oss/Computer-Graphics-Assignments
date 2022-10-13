#include "Surface.h"

Vec3f Surface::getRefractionRayDirection(Ray & r, HitRec & hitRec, bool inside) const{
    float etai = 1, etat = this->refractiveIndex;
    Vec3f n = hitRec.n;
    float eta;
    if(!inside) eta = etai / etat;
    else eta = etat;
    float cosi = -n.dot(r.d);
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return (r.d * eta + n* (eta * cosi - sqrtf(k))).normalize();
}

bool Surface::hit(const Ray &r, HitRec &rec, int *count) {
    return false;
}

void Surface::computeSurfaceHitFields(const Ray &r, HitRec &rec) const {

}

Ray Surface::computeRefractionRay(Ray ray, HitRec hitRec, int *count) {
    return {};
}

bool Surface::noSelfReflection(Ray ray, HitRec hitRec) {
    return false;
}
