#ifndef SHADER_H

#define SHADER_H

#include <stdbool.h>
#include <stdlib.h>
#include "custom_helpers.h"

typedef struct shader
{
    unsigned int ID;
    void (*use)(struct shader *self);
    void (*setUniformBool)(struct shader *self, const char *uniformVarName, bool val);
    void (*setUniformInt)(struct shader *self, const char *uniformVarName, int val);
    void (*setUniformFloat)(struct shader *self, const char *uniformVarName, float val);
    void (*setUniformV3F)(struct shader *self, const char *uniformVarName, float v1, float v2, float v3);
    void (*setUniformV4F)(struct shader *self, const char *uniformVarName, float v1, float v2, float v3, float v4);
} shader;

shader *init_shader(const char *vertex, const char *fragment);
void destroy_shader(shader *self);

#endif