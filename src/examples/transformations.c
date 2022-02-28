#include "examples/transformations.h"

int transformation_lesson(void)
{
    vec4 vec = {1.0f, 0.0f, 0.0f, 1.0f};

    mat4 mat = {{1.0f, 0.0f, 0.0f, 0.0f},
                {0.0f, 1.0f, 0.0f, 0.0f},
                {0.0f, 0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 0.0f, 1.0f}};

	glm_vec4_print(vec, stdout);
    glm_mat4_print(mat, stdout);

    glm_translate_make(mat, (vec3){1.0f, 1.0f, 0.0f});
	glm_mat4_mulv(mat, vec, vec);

    glm_mat4_print(mat, stdout);
	glm_vec4_print(vec, stdout);

    return 0;
}
