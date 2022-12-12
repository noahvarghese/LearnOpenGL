#ifndef SCENE_H
#define SCENE_H

#include <cglm/cglm.h>
#include "lib/shader.h"
#include "lib/texture.h"

typedef struct scene_t {
    unsigned int vao;
    texture_2d_t **textures;
    shader_t *shader;
    mat4 model;
    mat4 view;
    mat4 projection;
} scene_t;

scene_t *init_scene(unsigned int vao, texture_2d_t **textures, shader_t *shader);
void destroy_scene(scene_t *self);

#endif