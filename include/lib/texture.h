#ifndef TEXTURE_H

#define TEXTURE_H

#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/std_utils.h"

typedef struct texture_2d_t {
    GLuint texture_unit;
    unsigned int id;
    void (*bind)(struct texture_2d_t *self);
} texture_2d_t;

texture_2d_t *init_texture_2d(const char *image_path, GLint format, GLint internal_format, GLuint texture);
void destroy_texture_2d(texture_2d_t *self);

#endif