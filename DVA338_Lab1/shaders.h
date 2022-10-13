#include <string.h>
#include <fstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
using namespace std;


// Simple vertex shader treating vertex normals as RGB colors

typedef struct Shader_T {
    string name;
    string vs;
    string fs;
    GLuint id;
    Shader_T * next;
} Shader;
string getFileContent(string nameFile);
Shader * insertShader(string name, string vs, string fs);
//const char ** vs_n2c_src = getFileContent(vsFlatNameFile);

/*static const char * vs_n2c_src[] = {
        "#version 420 core\n"
        "\n"
        "in vec3 vPos;\n"
        "in vec3 vNorm;\n"
        "out vec4 color;\n"
        "uniform mat4 PV;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "    color = abs(vec4(vNorm, 1.0));\n"
        "    gl_Position = PV * vec4(vPos, 1.0f);\n"
        "}\n"
};
*/
// Simple fragment shader for color interpolation
/*static const char * fs_ci_src[] = {
	"#version 420 core                                                 \n"
	"                                                                  \n"
	"in vec4 color;                                                    \n"
	"out vec4 fColor;                                                  \n"
	"                                                                  \n"
	"void main(void)                                                   \n"
	"{                                                                 \n"
	"    fColor = color;                                               \n"
	"}                                                                 \n"
};*/



// The source code for additional shaders can be added here
// ...
