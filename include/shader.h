#ifndef SHADER_H

#define SHADER_H

#include <stdio.h>

typedef struct
{
    char *vertexCode;
    char *fragmentCode;
    FILE vShaderFile;
    FILE fShaderFile;
} Shader;

#endif
