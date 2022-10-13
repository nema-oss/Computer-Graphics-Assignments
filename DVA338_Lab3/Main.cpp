#include<vector>
#include<iostream>
#include<ctime>
using namespace std;

#include <glut.h>

#include "Vec3.h"
#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Camera.h"
#include "Triangle.h"
#include "Surface.h"
#include "TriangleLight.h"
#include <algorithm>

#define LIGHT_DENSITY 4
#define SUPERSAMPLE_RAYS 4 //4x4 rays per pixel
#define MAX_DEPTH 3
Vec3f bgColor = Vec3f(0.0f, 0.0f, 0.0f); //Blue
int intersectionTests=0;
bool shadowRays = true;
bool softShadows = true;
bool antialising = true;

class Scene {
public:
    vector<Sphere> spheres;
	vector<Triangle> triangles;
    Light light;
    TriangleLight triangleLight; //probably there's a better way to do this
    Camera camera;

	Scene() : light(Light()), camera(Camera()) {};
    Scene(Camera c) : light(Light()), camera(c) {};
    Scene(Light l, Camera c) : light(l), camera(c){};
    Scene(TriangleLight l, Camera c):triangleLight(l), camera(c){};
	void add(Sphere & s) {
		spheres.push_back(s);
        spheres[spheres.size()-1].id =  spheres.size()-1;
        s.id = spheres.size()-1;
		//cout << "Sphere added: " << "id = " << spheres[spheres.size()-1].id << endl;
        //spheres[spheres.size()-1].ks.print();
	}

    void add(Triangle & s) {
        triangles.push_back(s);
        triangles[triangles.size()-1].id =  triangles.size()-1;
        s.id = triangles.size()-1;
        //
        //cout << "Triangle added: " << "ka = " ; triangles[triangles.size()-1].ka.print();
    }

	void load(char * fileName) {
		// load a file with spheres for your scene here ...
		// Note: You do not have to do this as part of the assignment.
		// This is for the sake of convenience, if you want to save and setup many interesting scenes
	}

};


void glSetPixel(int x, int y, Vec3f & c) {
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

class SimpleRayTracer {
private: 
	Scene * scene;
	Image * image;

	Vec3f getEyeRayDirection(float x, float y) {
        //Uses a fix camera looking along the negative z-axis
		static float z = -5.0f;
		static float sizeX = 4.0f; 
		static float sizeY = 3.0f; 
		static float left = -sizeX * 0.5f;
		static float bottom = -sizeY * 0.5f;
		static float dx =  sizeX / float(image->getWidth());  
		static float dy =  sizeY / float(image->getHeight());

        Vec3f pixel = Vec3f(left + x * dx, bottom + y * dy, z).normalize();
        return Vec3f(pixel - scene->camera.position).normalize();
		return Vec3f(left + x * dx, bottom + y * dy, z).normalize();
        //Vec3f pixel = Vec3f(x / image->getWidth(),  y / image->getHeight(), 0);
        scene->camera.position = Vec3f(4,3,-5);
        return Vec3f(pixel - scene->camera.position).normalize();

	}


public:
	SimpleRayTracer(Scene * scene, Image * image) {
		this->scene = scene;
		this->image = image;
	}


    Camera getCamera(){
        return scene->camera;
    }

    void setCameraPosition(Vec3f position){
        scene->camera.position = position;
    }

    void setLight(Light l){
        scene->light = l;
    }

    void setLight(TriangleLight l){
        scene->triangleLight = l;
    }

    TriangleLight getTriangleLight(){
        return scene->triangleLight;
    }

	void searchClosestHit(const Ray & ray, HitRec & hitRec) {
		for (int i = 0; i < scene->triangles.size(); i++) {
            hitRec.anyHit = false;
			scene->triangles[i].hit(ray, hitRec, &intersectionTests);
            if(hitRec.anyHit)   {
                scene->triangles[i].computeSurfaceHitFields(ray, hitRec);
                hitRec.primIndex =i;
                break;
            }
		}
        for (int i = 0; i < scene->spheres.size(); i++) {
            //hitRec.anyHit = false;
            scene->spheres[i].hit(ray, hitRec, &intersectionTests);
            if(hitRec.anyHit){
                scene->spheres[i].computeSurfaceHitFields(ray, hitRec);
                hitRec.primIndex = i;
                break;
            }
        }
	}

    Vec3f getPhongColor(Light l, Vec3f N, HitRec hitRec, const Surface& surface, Ray ray, Vec3f V){
        Vec3f L = l.position - hitRec.p;
        Vec3f color = l.Ia.multCoordwise(surface.ka); //ambient;
        L = L.normalize();
        Vec3f R = N * (2 * L.dot(N)) - L;
        R = R.normalize();
        if (shadowRays) {
            HitRec shadowRec;
            Ray shadowRay;
            shadowRay.d = L;
            shadowRay.o = hitRec.p + N * Ray::rayEps;
            shadowRec.anyHit = false;
            searchClosestHit(shadowRay, shadowRec);

            if (!shadowRec.anyHit) {
                color += l.Id.multCoordwise(surface.kd) * max(L.dot(N), 0.0f);
                color += l.Is.multCoordwise(surface.ks) * pow(max(R.dot(V), 0.0f), surface.shininess);
            }
        } else {
            color += l.Id.multCoordwise(surface.kd) * max(L.dot(N), 0.0f);
            color += l.Is.multCoordwise(surface.ks) * pow(max(R.dot(V), 0.0f), surface.shininess);
        }
        return color;
    }

    Vec3f rayTrace(Ray & ray, HitRec & hitRec, int depth, bool show = false){
        if(depth==0){
            return {0.0,0.0,0.0};
        }
        depth--;
        Vec3f color = {0.0,0.0,0.0};
        Surface surface;

        switch(hitRec.surfaceHit){
            case SPHERE:
                surface = scene->spheres[hitRec.primIndex];
                break;
            case TRIANGLE:
                surface = scene->triangles[hitRec.primIndex];
                break;
        }

        HitRec reflectionRec;
        Ray reflectionRay;
        Vec3f N = hitRec.n;
        Vec3f V = -ray.d;
        if(!softShadows) {
            color += getPhongColor(scene->light, N, hitRec, surface, ray, V);

        } else {
            Vec3f sumOfColors = {0.0,0.0,0.0};
            for(int i=0; i<scene->triangleLight.numberOfLights; i++){
                Light l = scene->triangleLight.lights[i];
                sumOfColors += getPhongColor(l, N, hitRec, surface, ray, V);
            }
            color += sumOfColors * (1.0f/float(scene->triangleLight.numberOfLights));
        }

        Vec3f reflectionColor;
        reflectionRay.d = (ray.d - hitRec.n*2*ray.d.dot(hitRec.n)).normalize();
        reflectionRay.o = hitRec.p +  N * Ray::rayEps ;
        reflectionRec.anyHit = false;
        searchClosestHit(reflectionRay, reflectionRec);

        if(reflectionRec.anyHit){
            reflectionColor = rayTrace(reflectionRay, reflectionRec, depth);
        } else{
            reflectionColor = bgColor;
        }

        Vec3f refractionColor;
        if(surface.isTransparent){
            float facingRatio = -ray.d.dot(hitRec.n);
            float power = pow(1-facingRatio,3);
            float fresnelEffect = 0.1f + power*0.9f;
            Ray refractionRay = surface.computeRefractionRay(ray, hitRec, reinterpret_cast<int *>(intersectionTests));
            HitRec refractionRec;
            refractionRec.anyHit = false;
            searchClosestHit(refractionRay, refractionRec);
            if(refractionRec.anyHit) refractionColor=rayTrace(refractionRay, refractionRec, depth) * surface.refractiveIndex * (1-fresnelEffect);
            else refractionColor = bgColor * 0.9f; //to make the borders just a little visible
            reflectionColor = reflectionColor * fresnelEffect;
            color += (refractionColor + reflectionColor);
        } else{

            color = color*(1-surface.reflectiveNess) + reflectionColor * (surface.reflectiveNess);
        }
        return color;
    }

    static float getPerturbation(){
        return static_cast <float> (random()) / static_cast <float> (RAND_MAX);
    }
	void fireRays(void) { 
		Ray ray;
		HitRec hitRec;
		Vec3f Color = Vec3f(0.0f,0.0f, 0.0f);

		for (int y = 0; y < image->getHeight(); y++) {

			for (int x = 0; x < image->getWidth(); x++) {
                ray.o = scene->camera.position;
                ray.d = getEyeRayDirection(x,y);
                hitRec.anyHit = false;
                searchClosestHit(ray, hitRec);
                if (hitRec.anyHit) {
                    Color = Vec3f(0.0f, 0.0f, 0.0f);
                    if(antialising) {
                        //anti-alising with super sampling
                        for (int p = 0; p < SUPERSAMPLE_RAYS; p++) {
                            for (int q = 0; q < SUPERSAMPLE_RAYS; q++) {
                                ray.d = getEyeRayDirection(float(x) + (float(p) + getPerturbation()) / SUPERSAMPLE_RAYS,
                                                           float(y) +
                                                           (float(q) + getPerturbation()) / SUPERSAMPLE_RAYS);


                                if (x == 320 and y == 480) {
                                    Color += rayTrace(ray, hitRec, MAX_DEPTH, true); //for debugging purposes
                                } else Color += rayTrace(ray, hitRec, MAX_DEPTH);

                            }
                        }
                        Color = Color * float(1 / (pow(SUPERSAMPLE_RAYS, 2)));
                    }
                    else{
                        if (x == 330 and y == 240) {
                            Color += rayTrace(ray, hitRec, MAX_DEPTH, true); //for debugging purposes
                        } else{
                            Color += rayTrace(ray, hitRec, MAX_DEPTH);
                        }
                    }
                    image->setPixel(x, y, Color);
                    glSetPixel(x, y, Color);
                } else {
					image->setPixel(x, y, bgColor);
                    glSetPixel(x, y, bgColor);
				}
			}
		}

	}
};


SimpleRayTracer * rayTracer;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
	rayTracer->fireRays();
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = end.tv_sec - start.tv_sec;
    elapsed += (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Total rendering time: %f\n", elapsed);
    printf("Total number of intersection tests: %d\n", intersectionTests);
	glFlush();
}

void changeSize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glViewport(0,0,w,h);
}

void presetSphere(Scene * scene){
    Vec3f sphereAmbient1 = Vec3f(1,0.3,0.3);
    Vec3f sphereDiffuse1 = Vec3f(1,0.2,0.3);
    Vec3f sphereSpecular1 =  Vec3f(1, 0.2,0.3);
    Sphere s1(Vec3f(-3.0, 2.0, -15.0f), 1.5f, sphereAmbient1, sphereDiffuse1,sphereSpecular1, 27.8974f, 0.7f);
    scene->add(s1);
    cout<<s1.reflectiveNess<<endl;
    Vec3f sphereAmbient = Vec3f(0.0f, 1.0f, 0.0f);
    Vec3f sphereDiffuse = Vec3f(0.0f, 1.0f, 0.0f);
    Vec3f sphereSpecular =  Vec3f(0.0f, 1.0f, 0.0f);
    Sphere s(Vec3f(1.0f, 2.0f, -10.0f), 1.5f, sphereAmbient, sphereDiffuse,sphereSpecular, 27.8974f, 0.2f, 0.3f);
    //s.isTransparent=true;

    scene->add(s);

    sphereAmbient = {0.1f,0.1f,0.1f};
    sphereDiffuse = {0.1f,0.1f,0.1f};
    sphereSpecular={0.1f,0.1f,0.1f};
    Triangle triangle(Vec3f(0.0, -1.0,-1500.0), Vec3f(-100.0, -20.0, 0.0), Vec3f(100.0, -20.0, 0.0), sphereAmbient, sphereDiffuse,  sphereSpecular, 27.8974f, 0.0f);
    triangle.computeNormal();
    scene->add(triangle);


}



void presetAntiAlSphere(Scene * scene){
    Vec3f sphereAmbient1 = Vec3f(1,1,1);
    Vec3f sphereDiffuse1 = Vec3f(1,1,1);
    Vec3f sphereSpecular1 =  Vec3f(1,1,1);
    Sphere s1(Vec3f(-1.0, 0.0, -2.0f), 1.5f, sphereAmbient1, sphereDiffuse1,sphereSpecular1, 27.8974f, 0);
    scene->add(s1);
}
void presetTriangle(Scene * scene){


}



void presetTriangleLight(Scene * scene){
    Vec3f sphereAmbient = Vec3f(0.329412f, 0.223529f, 0.027451f);
    Vec3f sphereDiffuse = Vec3f(0.780392f, 0.568627f, 0.113725f);
    Vec3f sphereSpecular =  Vec3f(0.992157f, 0.941176f, 0.807843f);
    Sphere s(Vec3f(1.0f, 0.0f, -10.0f), 3.0f, sphereAmbient, sphereDiffuse,sphereSpecular, 27.8974f, 0.0);

    scene->add(s);
    softShadows = true;

}

void presetPointLight(){
    Vec3f p = Vec3f(8,10,-2);
    Vec3f ambient = Vec3f(0.2,0.2,0.2);
    Vec3f diffuse = Vec3f(1.0,1.0,1.0);
    Vec3f specular = Vec3f(1.0,1.0,1.0);
    Light light = Light(p,ambient,diffuse ,specular);
    rayTracer->setLight(light);
    softShadows=false;
}

void presetTriangleLight(){
    Vec3f v0 = Vec3f(8,10,-2);
    Vec3f v1 = Vec3f(8, 7, -2);
    Vec3f v2 = Vec3f(5, 10, -2);
    Vec3f ambient = Vec3f(0.2,0.2,0.2);
    Vec3f diffuse = Vec3f(1.0,1.0,1.0);
    Vec3f specular = Vec3f(1.0,1.0,1.0);
    TriangleLight triangleLight = TriangleLight(v0, v1, v2, LIGHT_DENSITY, ambient, diffuse, specular);
    rayTracer->setLight(triangleLight);
    softShadows = true;
}

void init(void)
{
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("SimpleRayTracer");
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	//glutKeyboardFunc(keypress);
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

	Scene * scene = new Scene;
	/* Make a sphere with radius of 3 */

    //presetTriangle(scene);
    //presetSphere(scene);
    //presetAntiAlSphere(scene);
    //presetRefraction(scene);
    //presetRefractionSpheres(scene);
	Image * image = new Image(640, 480);	

	rayTracer = new SimpleRayTracer(scene, image);
    //rayTracer->setCameraPosition({0.0,0.0,-3.0f});

    presetPointLight();
    //presetTriangleLight();

}


int main(int argc, char **argv) {

	glutInit(&argc, argv);
	init();
	glutMainLoop();
    return 0;
}
