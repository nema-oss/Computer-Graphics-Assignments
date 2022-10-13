#include "camera.h"

//Interface function for the projection matrix
//Note: Not all parameters may be needed, but the provided tests require this signature
Matrix ProjectionMatrix(Camera cam, int screenWidth, int screenHeight, ProjectionMode mode)
{
	Matrix P;

	// Assignment 1: Calculate the projection transform yourself 	
	// The matrix P should be calculated from camera parameters
	// Therefore, you need to replace this hard-coded transform.
	switch(mode){
        case ORTHOGONAL:
            P = OrthogonalTransform(20, -20, cam.nearPlane, cam.farPlane, 10, -10);
            break;
        case PERSPECTIVE:
            P = PerspectiveTransform(cam.fov, float(screenWidth)/float(screenHeight), cam.farPlane, cam.nearPlane);
            break;
    }

	return P;
}
//Interface function for view matrix
Matrix ViewMatrix(Camera cam)
{
	// Assignment 1: Calculate the transform to view coordinates yourself 	
	// The matrix V should be calculated from camera parameters
	// Therefore, you need to replace this hard-coded transform. 
	/*V.e[0] = 1.0f; V.e[4] = 0.0f; V.e[ 8] = 0.0f; V.e[12] =   0.0f;
	V.e[1] = 0.0f; V.e[5] = 1.0f; V.e[ 9] = 0.0f; V.e[13] =   0.0f;
	V.e[2] = 0.0f; V.e[6] = 0.0f; V.e[10] = 1.0f; V.e[14] = -cam.position.z;
	V.e[3] = 0.0f; V.e[7] = 0.0f; V.e[11] = 0.0f; V.e[15] =   1.0f;
*/
	return WorldToCamera(cam.rotation, cam.position);
}