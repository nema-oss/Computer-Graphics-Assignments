#ifndef _MESH_H_
#define _MESH_H_

#include "algebra.h"

typedef struct _Triangle {
	int vInds[3]; //vertex indices
} Triangle;

typedef struct _Mesh { 
	int nv;				
	Vector *vertices;
	Vector *vnorms;
	int nt;				
	Triangle *triangles;
	struct _Mesh *next; 
    Vector *scaling;
    Vector *translation;
    Vector *rotation;

    Vector ambient;
    Vector diffuse;
    Vector specular;
    float shininess;
	unsigned int vbo, ibo, vao; // OpenGL handles for rendering
} Mesh;

void insertModel(Mesh ** objlist, int nv, float * vArr, int nt, int * tArr, float scale = 1.0, Vector scaleV ={1.0,1.0,1.0}, Vector translate={0.0,0.0,0.0}, Vector rotate={0.0,0.0,0.0}, Vector ambient={1.0,1.0,1.0}, Vector diffuse={1.0,1.0,1.0}, Vector specular={1.0,1.0,1.0}, float shininess=1.0);

#endif
