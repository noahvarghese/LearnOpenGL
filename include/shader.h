#ifndef SHADER_H

#define SHADER_H

#include <stdbool.h>
#include <stdlib.h>
#include "custom_helpers.h"

typedef struct shader
{
    unsigned int ID;
    void (*use)(shader *self);
    void (*setUniformBool)(shader *self, const bool *val);
    void (*setUniformInt)(shader *self, const bool *val);
    void (*setUniformFloat)(shader *self, const bool *val);
} shader;

shader *init_shader(const char *vertex, const char *fragment);
void destroy_shader(shader *self);

#endif