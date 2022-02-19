#ifndef SHADER_H

#define SHADER_H

#include <stdio.h>

typedef struct
{
    const char *vertexCode;
    const char *fragmentCode;
    FILE vShaderFile;
    FILE fShaderFile;
} Shader;

#endif
