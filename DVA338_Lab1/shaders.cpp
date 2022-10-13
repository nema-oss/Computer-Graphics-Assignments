#include <string.h>
#include <fstream>
#include "shaders.h"

using namespace std;

string getFileContent(string nameFile){
    ifstream file;
    file.open(nameFile, ios::in);
    string contents((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    file.close();
    //printf("%s", contents.c_str());
    return strcat(const_cast<char *>(contents.c_str()), "\n");
}

Shader * insertShader(string name, string vs, string fs){
    Shader * shader = (Shader * )malloc(sizeof(Shader));
    shader->name = name;
    shader->vs = vs;
    shader->fs=fs;
    shader->next = NULL;
    return shader;
}
