#include "lib/scene.h"

scene_t *init_scene(unsigned int vao, texture_2d_t **textures, shader_t *shader) {
    scene_t *self;
    self = (scene_t *)malloc(sizeof(scene_t));
    if (self == NULL)
    {
        error("Unable to allocate memory for scene");
    }
    self->vao = vao;
    self->textures = textures;
    self->shader = shader;


    // setup camera
    glm_mat4_identity(self->model);
    glm_mat4_identity(self->view);
    glm_mat4_identity(self->projection);

    return self;
}

void destroy_scene(scene_t *self) {
    glDeleteVertexArrays(1, &self->vao);

    destroy_shader(self->shader);

    texture_2d_t **texture = self->textures;
    while(*texture) {
        destroy_texture_2d(*texture);
        ++texture;
    }

    free(self);
}