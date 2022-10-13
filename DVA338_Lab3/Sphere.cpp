
#include "Sphere.h"


bool Sphere::hit(const Ray & r, HitRec & rec, int * count) {
    *(count) = *(count) + 1;
	Vec3f v = c - r.o;
	float s = v.dot(r.d);
	float vLenSq = v.dot(v);
	float radSq = this->r * this->r; 
	if (s < 0 && vLenSq > radSq) {
		return false;
	}
	float mSq = vLenSq - s * s;
	if (mSq > radSq) {
		return false;
	}

    Vec3f v_ = Vec3f (-v.x, -v.y, -v.z);
    float A = 1;
    float B = 2 * v_.dot(r.d);
    float C = v_.dot(v_)-radSq;
    float D = B*B - 4*A*C;
    if(D>=0){
        float d = sqrt(D);
        float t1 = (-B - d) / (2 * A);
        float t2 = (-B + d) / (2 * A);

        if(t1<t2) {

                rec.tHit = t1;
                rec.anyHit = true;
                rec.surfaceHit = SPHERE;
                return true;

        }
        else {
                rec.tHit = t2;
                rec.anyHit = true;
                rec.surfaceHit=SPHERE;
                return true;

        }
    }
    return false;

}


void Sphere::computeSurfaceHitFields(const Ray & r, HitRec & rec) const {
	rec.p = r.o + r.d * rec.tHit;
	rec.n = (rec.p - c).normalize();
}

Ray Sphere::computeRefractionRay(Ray ray, HitRec hitRec, int *count) {
    Ray innerRay, refractionRay;
    HitRec innerRec;
    innerRay.d = getRefractionRayDirection(ray, hitRec, false);
    innerRay.o = hitRec.p + hitRec.n * ray.rayEps; //adding some wiggle room so that the first intersection it finds will have a negative t since it's behind
                                                    // the origin of the ray -- hopefully
    hit(innerRay, innerRec, count);
    computeSurfaceHitFields(innerRay, innerRec);

    //refractionRay.d = getRefractionRayDirection(innerRay, innerRec, true);
    refractionRay.d = ray.d;
    refractionRay.o = innerRec.p + innerRec.n * ray.rayEps;
    return refractionRay;
}

bool Sphere::noSelfReflection(Ray ray, HitRec hitRec) {//(x-c)^2 <= r^2
    return pow(hitRec.p.x - this->c.x,2) + pow(hitRec.p.y-this->c.y,2) + pow(hitRec.p.z - this->c.z, 2) <= pow(this->r, 2);
}
