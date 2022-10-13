#include <stdlib.h>
#include "mesh.h"
#include <assert.h>
#include <cstdio>

float rnd() {
	return 2.0f * float(rand()) / float(RAND_MAX) - 1.0f;
}

void insertModel(Mesh** list, int nv, float* vArr, int nt, int* tArr,float scale, Vector scaleV, Vector translate, Vector rotate, Vector ambient, Vector diffuse, Vector specular, float shininess) {
    Vector faceNormal={0,0,0};

	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	mesh->nv = nv;
	mesh->nt = nt;

	mesh->vertices = (Vector*)malloc(nv * sizeof(Vector));
	mesh->vnorms = (Vector*)malloc(nv * sizeof(Vector));
	mesh->triangles = (Triangle*)malloc(nt * sizeof(Triangle));

    mesh->translation = (Vector*)malloc(sizeof(Vector));
    mesh->rotation = (Vector*)malloc(sizeof(Vector));
    mesh->scaling = (Vector*)malloc(sizeof(Vector));

    *(mesh->translation)= {translate.x,translate.y,translate.z};
    *(mesh->rotation)={rotate.x, rotate.y, rotate.z};
    *(mesh->scaling) = {scaleV.x,scaleV.y,scaleV.z};

    mesh->ambient = ambient;
    mesh->diffuse = diffuse;
    mesh->specular =specular;
    mesh->shininess = shininess;

	// set mesh vertices
	for (int i = 0; i < nv; i++) {
		mesh->vertices[i].x = vArr[i * 3] * scale;
		mesh->vertices[i].y = vArr[i * 3 + 1] * scale;
		mesh->vertices[i].z = vArr[i * 3 + 2] * scale;
        mesh->vnorms[i] = {0,0,0}; //initialize norms to 0
	}

	// set mesh triangles
	for (int i = 0; i < nt; i++) {
		mesh->triangles[i].vInds[0] = tArr[i * 3];
		mesh->triangles[i].vInds[1] = tArr[i * 3 + 1];
		mesh->triangles[i].vInds[2] = tArr[i * 3 + 2];
        int i1 = mesh->triangles[i].vInds[0];
        int i2 = mesh->triangles[i].vInds[1];
        int i3 = mesh->triangles[i].vInds[2];
        faceNormal = SurfaceNormal(mesh->vertices[i1], mesh->vertices[i2], mesh->vertices[i3]); //in order to find the vertex normal, just sum the surface normals according
                                                                                                        // to the vertex index (i1, i2, i3) and then normalize below
        mesh->vnorms[i1] = Add(mesh->vnorms[i1], faceNormal);
        mesh->vnorms[i2] = Add(mesh->vnorms[i2], faceNormal);
        mesh->vnorms[i3] = Add(mesh->vnorms[i3], faceNormal);
	}

	// Assignment 1: 
	// Calculate and store suitable vertex normals for the mesh here.
	// Replace the code below that simply sets some arbitrary normal values	
	// Note: You need to fix the implementation of the SurfaceNormal function we give you
	// as currently it returns a constant value
	for (int i = 0; i < nv; i++) {
        mesh->vnorms[i] = Normalize(mesh->vnorms[i]);
	}
	mesh->next = *list;
	*list = mesh;
}
