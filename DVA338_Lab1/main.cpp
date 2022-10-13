//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#ifdef _WINDOWS
	//If you follow the setup instructions provided for Visual Studio
	//The include path specified already includes "GL", so we can ignore it
	#include <glew.h>
	#include <freeglut.h>
#elif defined(__APPLE__)
	#include <GL/glew.h>
	#include <GL/glut.h>
#else
	#include <GL/glew.h>
	#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>

#endif
#include "camera.h"	//algebra is included in camera.h
#include "shaders.h"
#include "mesh.h"
#include <stdio.h>
//Uncomment if you want to run the tests before the graphics starts
//#define ENABLE_TESTING


Camera cam = {{0,0,20}, {0,0,0}, 60, 1, 10000}; // Setup the global camera parameters
ProjectionMode mode = PERSPECTIVE;

int screen_width = 1024;
int screen_height = 768;

Mesh *meshList = NULL; // Global pointer to linked list of triangle meshes
Mesh *selectedMesh = meshList; //selected mesh to animate

Vector lightPos = {10,10,10};
Vector ambientLight = {0.2,0.2,0.2};
Vector diffuseLight = {1.0,1.0,1.0};
Vector specularLight = {1.0,1.0,1.0};

Shader * shaderList = NULL;
Shader * selectedShader = NULL;

GLuint shprg; // Shader program id
GLuint furShader;
int applyFurShading=0;

// Global transform matrices
// V is the view transform
// P is the projection transform
// PV = P * V is the combined view-projection transform
Matrix V, P, PV;

void prepareFurShaderProgram(const char ** vs_src, const char ** fs_src){
    GLint success = GL_FALSE;
    furShader = glCreateProgram();
    //printf("%s", fs_src[0]);
    //printf("%d\n", vs_src==NULL);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, vs_src, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Error in vertex shader!\n");
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(vs); // Don't leak the shader.
        return;
    }
    else printf("Vertex shader compiled successfully!\n");
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    string c = getFileContent("/home/nema/DevOgl/DVA338_Lab1/GeometryFurShader.txt");
    const char * gShaderCode = c.c_str();
    //printf("%s", gShaderCode);
    glShaderSource(geometryShader, 1, &gShaderCode, NULL);
    glCompileShader(geometryShader);
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Error in geometry shader!\n");
        GLint maxLength = 0;
        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(geometryShader, maxLength, &maxLength, &errorLog[0]);
        for(char i: errorLog)
            printf("%c", i);
            // Provide the infolog in whatever manor you deem best.
            // Exit with failure.
            glDeleteShader(geometryShader); // Don't leak the shader.
            return;
        }
    else printf("Geometry shader compiled successfully!\n");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, fs_src, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Error in fragment shader!\n");
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fs); // Don't leak the shader.
        return;
    }
    else printf("Fragment shader compiled successfully!\n");

    glAttachShader(furShader, vs);

    glAttachShader(furShader, geometryShader);

    glAttachShader(furShader, fs);
    glLinkProgram(furShader);
    GLint isLinked = GL_FALSE;
    glGetProgramiv(furShader, GL_LINK_STATUS, &isLinked);
    if (!isLinked){
        printf("Link error in shader program!\n");
        GLint maxLength = 0;
        glGetProgramiv(furShader, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(furShader, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
    }
    else printf("Shader program linked successfully!\n");
}


void prepareShaderProgram(const char ** vs_src, const char ** fs_src) {
	GLint success = GL_FALSE;
	shprg = glCreateProgram();
    selectedShader->id = shprg;
    //printf("%s", fs_src[0]);
    //printf("%d\n", vs_src==NULL);
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_src, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
        printf("Error in vertex shader!\n");
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(vs); // Don't leak the shader.
        return;
    }
	else printf("Vertex shader compiled successfully!\n");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_src, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        printf("Error in fragment shader!\n");
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fs); // Don't leak the shader.
        return;
    }
    else printf("Fragment shader compiled successfully!\n");
	glAttachShader(shprg, vs);
    glAttachShader(shprg, fs);
	glLinkProgram(shprg);
	GLint isLinked = GL_FALSE;
	glGetProgramiv(shprg, GL_LINK_STATUS, &isLinked);
	if (!isLinked){
        printf("Link error in shader program!\n");
        GLint maxLength = 0;
        glGetProgramiv(shprg, GL_INFO_LOG_LENGTH, &maxLength);
        vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(shprg, maxLength, &maxLength, &errorLog[0]);

        for(char i: errorLog)
            printf("%c", i);
    }
	else printf("Shader program linked successfully!\n");
}

void prepareMesh(Mesh *mesh) {
	int sizeVerts = mesh->nv * 3 * sizeof(float);
	int sizeCols  = mesh->nv * 3 * sizeof(float);
	int sizeTris = mesh->nt * 3 * sizeof(int);
	
	// For storage of state and other buffer objects needed for vertex specification
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// Allocate VBO and load mesh data (vertices and normals)
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeVerts + sizeCols , NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVerts, (void *)mesh->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeVerts, sizeCols, (void *)mesh->vnorms);

	// Allocate index buffer and load mesh indices
	glGenBuffers(1, &mesh->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeTris, (void *)mesh->triangles, GL_STATIC_DRAW);

	// Define the format of the vertex data
	GLint vPos = glGetAttribLocation(shprg, "vPos");
	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Define the format of the vertex data 
	GLint vNorm = glGetAttribLocation(shprg, "vNorm");
	glEnableVertexAttribArray(vNorm);
	glVertexAttribPointer(vNorm, 3, GL_FLOAT, GL_FALSE, 0, (void *)(mesh->nv * 3 *sizeof(float)));

    glBindVertexArray(0);

}

void renderMesh(Mesh *mesh) {
	
	// Assignment 1: Apply the transforms from local mesh coordinates to world coordinates here
	// Combine it with the viewing transform that is passed to the shader below
    Matrix T = Translate(mesh->translation->x, mesh->translation->y, mesh->translation->z);

    Matrix Rx = RotateX(mesh->rotation->x);
    Matrix Ry = RotateY(mesh->rotation->y);
    Matrix Rz = RotateZ(mesh->rotation->z);
    Matrix S = Scale(mesh->scaling->x, mesh->scaling->y, mesh->scaling->z);

    Matrix W = MatMatMul(MatMatMul(MatMatMul(MatMatMul(T, Rx),Ry),Rz), S);

    Matrix M = MatMatMul(V, W);
	// Pass the viewing transform to the shader
    PV = MatMatMul(P, M);

	GLint loc_PV = glGetUniformLocation(shprg, "PV");
	glUniformMatrix4fv(loc_PV, 1, GL_FALSE, PV.e);

    GLint loc_VMatrix = glGetUniformLocation(shprg, "VMatrix");
    glUniformMatrix4fv(loc_VMatrix, 1, GL_FALSE, V.e);

    GLint loc_IA = glGetUniformLocation(shprg, "Ia");
    glUniform3f(loc_IA, ambientLight.x, ambientLight.y, ambientLight.z);

    GLint loc_ID = glGetUniformLocation(shprg, "Id");
    glUniform3f(loc_ID, diffuseLight.x, diffuseLight.y, diffuseLight.z);

    GLint loc_IS = glGetUniformLocation(shprg, "Is");
    glUniform3f(loc_IS, specularLight.x, specularLight.y, specularLight.z);

    GLint loc_light = glGetUniformLocation(shprg, "light");
    glUniform3f(loc_light, lightPos.x, lightPos.y, lightPos.z);

    GLint loc_alfa = glGetUniformLocation(shprg, "alfa");
    glUniform1f(loc_alfa, mesh->shininess);

    GLint loc_ka = glGetUniformLocation(shprg, "ka");
    glUniform3f(loc_ka, mesh->ambient.x, mesh->ambient.y, mesh->ambient.z);

    GLint loc_kd = glGetUniformLocation(shprg, "kd");
    glUniform3f(loc_kd, mesh->diffuse.x, mesh->diffuse.y, mesh->diffuse.z);

    GLint loc_ks = glGetUniformLocation(shprg, "ks");
    glUniform3f(loc_ks, mesh->specular.x, mesh->specular.y, mesh->specular.z);

    GLint loc_MV = glGetUniformLocation(shprg, "MV");
    glUniformMatrix4fv(loc_MV, 1, GL_FALSE, M.e);

    GLint loc_W = glGetUniformLocation(shprg, "W");
    glUniformMatrix4fv(loc_W, 1, GL_FALSE, W.e);
    // Select current resources
	glBindVertexArray(mesh->vao);
	
	// To accomplish wireframe rendering (can be removed to get filled triangles)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
	// Draw all triangles
	glDrawElements(GL_TRIANGLES, mesh->nt * 3, GL_UNSIGNED_INT, NULL); 
	glBindVertexArray(0);
}



void display(void) {
	Mesh *mesh;
	
	glClear(GL_COLOR_BUFFER_BIT);	

	/*
	TODO: Assignment 1: The implementation of View- and ProjectionMatrix in camera.cpp 
	returns hardcoded matrices. Your assignment is to fix them.
	*/
	V = ViewMatrix(cam);
	
	P = ProjectionMatrix(cam, screen_width, screen_height, mode);
	
	// This finds the combined view-projection matrix
	PV = MatMatMul(P, V);

	// Select the shader program to be used during rendering 


	// Render all meshes in the scene
	mesh = meshList;
		
	while (mesh != NULL) {
        glUseProgram(shprg);
		renderMesh(mesh);
        if(applyFurShading==1){
            glUseProgram(furShader);
            renderMesh(mesh);
        }
		mesh = mesh->next;

	}
	glFlush();
}

void changeSize(int w, int h) {
	screen_width = w;
	screen_height = h;
	glViewport(0, 0, screen_width, screen_height);

}

void init(void) {
    // Compile and link the given shader program (vertex shader and fragment shader)

    string vsContent;
    string fsContent;
    const char *vs_n2c_src;
    const char *fs_ci_src;

    while(selectedShader!=NULL){
        vsContent = getFileContent(selectedShader->vs);
        fsContent = getFileContent(selectedShader->fs);

        vs_n2c_src = vsContent.c_str();
        fs_ci_src = fsContent.c_str();
        prepareShaderProgram(&vs_n2c_src, &fs_ci_src);
        selectedShader=selectedShader->next;
    }
    selectedShader = shaderList;
    vsContent = getFileContent("/home/nema/DevOgl/DVA338_Lab1/vsFur.txt");
    fsContent = getFileContent("/home/nema/DevOgl/DVA338_Lab1/fsFur.txt");

    vs_n2c_src = vsContent.c_str();
    fs_ci_src = fsContent.c_str();
    prepareFurShaderProgram(&vs_n2c_src, &fs_ci_src);


    // Setup OpenGL buffers for rendering of the meshes
    Mesh * mesh = meshList;
    while (mesh != NULL) {
        prepareMesh(mesh);
        mesh = mesh->next;
    }
}

void keypress(unsigned char key, int x, int y) {
	switch(key) {
	case 'z':
		cam.position.z -= 0.2f;
		break;
	case 'Z':
		cam.position.z += 0.2f;
		break;
    case 'x':
        cam.position.x -= 0.2f;
        break;
    case 'X':
        cam.position.x += 0.2f;
        break;
    case 'y':
        cam.position.y -=0.2f;
        break;
    case 'Y':
        cam.position.y += 0.2f;
    case 'i':
        cam.rotation.x -= 0.2f;
        break;
    case 'I':
        cam.rotation.x +=0.2f;
        break;
    case 'j':
        cam.rotation.y -=0.2f;
        break;
    case 'J':
        cam.rotation.y +=0.2f;
        break;
    case 'k':
        cam.rotation.z -=0.2f;
        break;
    case 'K':
        cam.rotation.z +=0.2f;
        break;
    case 'm':
        mode = PERSPECTIVE;
        break;
    case 'M':
        mode = ORTHOGONAL;
        break;
    case 'o':
        cam.fov -=0.2f;
        break;
    case 'O':
        cam.fov +=0.2f;
        break;
    case 'n':
        cam.nearPlane -=0.2f;
        break;
    case 'N':
        cam.nearPlane +=0.2f;
        break;
    case 'f':
        cam.farPlane -=1000;
        break;
    case 'F':
        cam.farPlane +=1000;
        break;
    case 'w':
        if(selectedMesh->next==NULL){
            selectedMesh = meshList;
        }
        else{
            selectedMesh = selectedMesh->next;
        }
        break;
    case 'r':
        selectedMesh->rotation->x+=0.2f;
        selectedMesh->rotation->y+=0.2f;
        selectedMesh->rotation->z+=0.2f;
        break;
    case 'R':
        selectedMesh->rotation->x-=0.2f;
        selectedMesh->rotation->y-=0.2f;
        selectedMesh->rotation->z-=0.2f;
        break;
    case 's':
        selectedMesh->scaling->x+=0.2f;
        selectedMesh->scaling->y+=0.2f;
        selectedMesh->scaling->z+=0.2f;
        break;
    case 'S':
        selectedMesh->scaling->x-=0.2f;
        selectedMesh->scaling->y-=0.2f;
        selectedMesh->scaling->z-=0.2f;
        break;
    case 't':
        selectedMesh->translation->x+=0.2f;
        selectedMesh->translation->y+=0.2f;
        selectedMesh->translation->z+=0.2f;
        break;
    case 'T':
        selectedMesh->translation->x-=0.2f;
        selectedMesh->translation->y-=0.2f;
        selectedMesh->translation->z-=0.2f;
        break;
    case 'g': {
        if (selectedShader->next == NULL) {
            selectedShader = shaderList;
        } else {
            selectedShader = selectedShader->next;
        }
        shprg = selectedShader->id;
        //init();
        //printf("camera: %f %f %f\n", cam.position.x, cam.position.y, cam.position.z);
        //printf("mesh:\n\tscaling: %f %f %f\n", selectedMesh->scaling->x, selectedMesh->scaling->y, selectedMesh->scaling->z);
        break;
    }
	case 'Q':
        glutLeaveMainLoop();
        break;
	case 'q':		
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}


void cleanUp(void) {	
	printf("Running cleanUp function... ");
	// Free openGL resources
	// ...

	// Free meshes
	// ...
	printf("Done!\n\n");
}

// Include data for some triangle meshes (hard coded in struct variables)
#include "./models/mesh_bunny.h"
#include "./models/mesh_cow.h"
#include "./models/mesh_cube.h"
#include "./models/mesh_frog.h"
#include "./models/mesh_knot.h"
#include "./models/mesh_sphere.h"
#include "./models/mesh_teapot.h"
#include "./models/mesh_triceratops.h"

#ifdef ENABLE_TESTING
#include "./test/camera_tests.h"
#include "./test/math_tests.h"
#endif

int main(int argc, char **argv) {
	// Setup freeGLUT

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow("DVA338 Programming Assignments");
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(keypress);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Specify your preferred OpenGL version and profile
	glutInitContextVersion(4, 5);
	//glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);	
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Uses GLEW as OpenGL Loading Library to get access to modern core features as well as extensions
	GLenum err = glewInit(); 
	if (GLEW_OK != err) { fprintf(stdout, "Error: %s\n", glewGetErrorString(err)); return 1; }

	// Output OpenGL version info
	fprintf(stdout, "GLEW version: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "OpenGL version: %s\n", (const char *)glGetString(GL_VERSION));
	fprintf(stdout, "OpenGL vendor: %s\n\n", glGetString(GL_VENDOR));

    string fsFlatNameFile = "/home/nema/DevOgl/DVA338_Lab1/fragmentShaderFlat.txt";
    string fsSmoothNameFile = "/home/nema/DevOgl/DVA338_Lab1/fragmentShaderSmooth.txt";
    string vsFlatNameFile = "/home/nema/DevOgl/DVA338_Lab1/vertexShaderFlat.txt";
    string vsSmoothNameFile = "/home/nema/DevOgl/DVA338_Lab1/vertexShaderSmooth.txt";

    shaderList = insertShader("Smooth", vsSmoothNameFile, fsSmoothNameFile);
    shaderList->next = insertShader("Flat", vsFlatNameFile, fsFlatNameFile);

    selectedShader = shaderList;
	// Insert the 3D models you want in your scene here in a linked list of meshes
	// Note that "meshList" is a pointer to the first mesh and new meshes are added to the front of the list	
	//insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
    //insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
	//insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
	//insertModel(&meshList, bunny.nov, bunny.verts, bunny.nof, bunny.faces, 60.0);	
	//insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0);
	//insertModel(&meshList, frog.nov, frog.verts, frog.nof, frog.faces, 2.5);
	//insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
	//insertModel(&meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, 12.0);
	//insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 3.0);

    switch(atoi(argv[1])){
        case 2:
            insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0);
            insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0);
            selectedMesh = meshList; //selected mesh to animate
            cam.position={-5,-5,20};
            cam.rotation={-10,-30,-45};
            break;
        case 3:
            insertModel(&meshList, knot.nov, knot.verts, knot.nof, knot.faces, 1.0);
            selectedMesh = meshList; //selected mesh to animate
            mode = ORTHOGONAL;
            break;
        case 5:
            insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0,{1.0,1.0,1.0}, {10,0,0},{0,90,0});
            insertModel(&meshList, cow.nov, cow.verts, cow.nof, cow.faces, 20.0, {3,1,1},{0,30,-40});
            insertModel(&meshList, triceratops.nov, triceratops.verts, triceratops.nof, triceratops.faces, 3.0,{1.0,1.0,1.0},{-25,0,0}, {60,0,0});
            selectedMesh = meshList; //selected mesh to animate
            cam.fov=120;
            break;
        case 6:
            cam.position = {20,20,30};
            cam.rotation = {-45, 30, 0};
            cam.fov = 60;
            insertModel(&meshList, teapot.nov, teapot.verts, teapot.nof, teapot.faces, 2.0, {1,1,1}, {0,0,0},{-90,0,0},{0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 27.8974f);
            insertModel(&meshList, cube.nov, cube.verts, cube.nof, cube.faces, 5.0, {4.0,0.2,4.0}, {0,0,0},{0,0,0},{0.05375f, 0.05f, 0.06625f}, {0.18275f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, 38.4f);
            break;
        case 7:
            insertModel(&meshList, sphere.nov, sphere.verts, sphere.nof, sphere.faces, 1.0, {1,1,1}, {0,0,17}, {0,0,0}, {0.05375f, 0.05f, 0.06625f}, {0.5f, 0.22525f, 0.22525f}, {0.5f, 0.22525f, 0.22525f}, 38.4f);
            selectedShader = selectedShader->next;
            //printf("Selected shader: %s\n", selectedShader->name.c_str());
            applyFurShading=1;

            break;
    }


    selectedMesh = meshList; //selected mesh to animate


	#ifdef ENABLE_TESTING
	printf("----BEGIN TESTS---\n");
	/* Runs some tests. If you've done up to assignment 1.3, these should pass */
	if (run_camera_tests())
	{
		printf("Some camera tests did not pass\n");
	}

	/* These should pass if you've done 1.4 */
	if(run_math_tests())
	{
		printf("Some math tests did not pass\n");
	}
	printf("----END TESTS---\n");
	#endif

	init();


    glutMainLoop();

	cleanUp();
	return 0;
}
