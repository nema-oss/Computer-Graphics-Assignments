#define _USE_MATH_DEFINES // To get M_PI defined
#include <math.h>
#include <stdio.h>
#include "algebra.h"

Vector CrossProduct(Vector a, Vector b) {
	Vector v = { a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
	return v;
}

float DotProduct(Vector a, Vector b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector Subtract(Vector a, Vector b) {
	Vector v = { a.x-b.x, a.y-b.y, a.z-b.z };
	return v;
}    

Vector Add(Vector a, Vector b) {
	Vector v = { a.x+b.x, a.y+b.y, a.z+b.z };
	return v;
}    

float Length(Vector a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

Vector Normalize(Vector a) {
	float len = Length(a);
	Vector v = { a.x/len, a.y/len, a.z/len };
	return v;
}

Vector ScalarVecMul(float t, Vector a) {
	Vector b = { t*a.x, t*a.y, t*a.z };
	return b;
}

HomVector MatVecMul(Matrix a, Vector b) {
	HomVector h;
	h.x = b.x*a.e[0] + b.y*a.e[4] + b.z*a.e[8] + a.e[12];
	h.y = b.x*a.e[1] + b.y*a.e[5] + b.z*a.e[9] + a.e[13];
	h.z = b.x*a.e[2] + b.y*a.e[6] + b.z*a.e[10] + a.e[14];
	h.w = b.x*a.e[3] + b.y*a.e[7] + b.z*a.e[11] + a.e[15];
	return h;
}

Vector Homogenize(HomVector h) {
	Vector a;
	if (h.w == 0.0) {
		fprintf(stderr, "Homogenize: w = 0\n");
		a.x = a.y = a.z = 9999999;
		return a;
	}
	a.x = h.x / h.w;
	a.y = h.y / h.w;
	a.z = h.z / h.w;
	return a;
}

Matrix MatMatMul(Matrix a, Matrix b) {
	Matrix c;
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			c.e[j*4+i] = 0.0;
			for (k = 0; k < 4; k++)
				c.e[j*4+i] += a.e[k*4+i] * b.e[j*4+k];
		}
	}
	return c;
}

void PrintVector(char const *name, Vector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z);
}

void PrintHomVector(char const *name, HomVector a) {
	printf("%s: %6.5lf %6.5lf %6.5lf %6.5lf\n", name, a.x, a.y, a.z, a.w);
}

void PrintMatrix(char const *name, Matrix a) { 
	int i,j;

	printf("%s:\n", name);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			printf("%6.5lf ", a.e[j*4+i]);
		}
		printf("\n");
	}
}

//Given three points on a surface, returns the surface normal
Vector SurfaceNormal(Vector a, Vector b, Vector c)
{
    Vector x = Subtract(b,a);
    Vector y = Subtract(c, a);
    Vector res = Normalize(CrossProduct(x,y));
    return res;
	/* Lab 1: Calculate the actual surface normals */
	//return {0.80078125f,0.34765625f, 0.1796875f};
}

Matrix CreateDiagonalMatrix(){
    Matrix T;
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
                T.e[j*4+i] = 0.0;
        }
    }
    T.e[0]=1.0;
    T.e[5]=1.0;
    T.e[10]=1.0;
    T.e[15]=1.0;
    return T;
}

Matrix Translate(float dx, float dy, float dz){
    Matrix T = CreateDiagonalMatrix();
    T.e[12]=dx;
    T.e[13]=dy;
    T.e[14]=dz;
    return T;
}

Matrix RotateX(float angle){
    Matrix R = CreateDiagonalMatrix();
    float sine=sin(angle*M_PI/180), cosine=cos(angle*M_PI/180);
    R.e[5]=cosine;
    R.e[9]=-sine;
    R.e[6]=sine;
    R.e[10]=cosine;
    return R;
}

Matrix RotateY(float angle){
    Matrix R = CreateDiagonalMatrix();
    float sine=sin(angle*M_PI/180), cosine=cos(angle*M_PI/180);
    R.e[0]=cosine;
    R.e[2]=-sine;
    R.e[8]=sine;
    R.e[10]=cosine;
    return R;
}

Matrix RotateZ(float angle){
    Matrix R = CreateDiagonalMatrix();
    float sine=sin(angle*M_PI/180), cosine=cos(angle*M_PI/180);
    R.e[0]=cosine;
    R.e[4]=-sine;
    R.e[1]=sine;
    R.e[5]=cosine;
    return R;
}

Matrix Scale(float dx, float dy, float dz){
    Matrix S = CreateDiagonalMatrix();
    S.e[0]=dx;
    S.e[5]=dy;
    S.e[10]=dz;
    return S;
}

Matrix WorldToCamera(Vector rot, Vector c){
    Matrix Rz = RotateZ(-rot.z);
    Matrix Ry = RotateY(-rot.y);
    Matrix Rx = RotateX(-rot.x);
    Matrix T = Translate(-c.x, -c.y, -c.z);
    return MatMatMul(MatMatMul(MatMatMul(Rz, Ry), Rx),T);
}

Matrix OrthogonalTransform(float right, float left, float near, float far, float top, float bottom){
    Matrix P=CreateDiagonalMatrix();
    P.e[0] = 2/(right-left);
    P.e[5]=2/(top-bottom);
    P.e[10]=2/(near-far);

    P.e[12]=-(right+left)/(right-left);
    P.e[13]=-(top+bottom)/(top-bottom);
    P.e[14]=-(far+near)/(far-near);
    return P;
}

Matrix PerspectiveTransform(float fov, float aspect, float far, float near){
    Matrix P = CreateDiagonalMatrix();
    float cotan = 1/tan((fov*M_PI/180)/2);
    P.e[0] = cotan/aspect;
    P.e[5]=cotan;
    P.e[10]=(near+far)/(near-far);
    P.e[15]=0.0;
    P.e[14]=2*far*near/(near-far);
    P.e[11]=-1.0;
    return P;
}

Matrix Transpose(Matrix A){
    Matrix B;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){

        }
    }
    return B;
}
