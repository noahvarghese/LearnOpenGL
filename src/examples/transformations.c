#include "examples/transformations.h"

#define DEBUG
#define _DEBUG
#define CGLM_DEFINE_PRINTS

int transformation_lesson(void)
{
    // vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};
    printf("HELLO\n");

    mat4 mat = {{1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0, 0.0f, 1.0f}};

    glm_mat4_print(mat, stdout);
    glm_mat4_print(mat, stderr);
    fflush(stdout);

    glm_translate_make(mat, (vec3){1.0f, 1.0f, 0.0f});

    glm_mat4_print(mat, stdout);
    fflush(stdout);

    return 0;
}