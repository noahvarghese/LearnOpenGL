#include "1.getting_started/6.3.camera/camera.h"

// static float vertices[] = {
//      // vertex            // texture coordinate
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
// };
    
vec3 cube_positions[10] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

static struct uniforms_t{
    const char *texture0;
    const char *model;
    const char *view;
    const char *projection;
} uniforms = {
    "texture0",
    "model",
    "view",
    "projection"
};

static scene_t *scene;
static window_manager_t *window_manager;

static void process_inputs() {
    if (window_manager->poll_for_key_input(window_manager, GLFW_KEY_ESCAPE))
    {
        window_manager->close_window(window_manager);
    }
}

static void gen_cube_positions(vec3 buffer[], int num_cubes) {
    srand(time(0));

    float x;
    float y;
    float z;

    for (int i = 0; i < num_cubes; i++) {
        // restrict x and y to range (-1.0, 1.0)
        x = ((rand() / (float)RAND_MAX) * 20.0f) - 10.0f;
        y = ((rand() / (float)RAND_MAX) * 20.0f) - 10.0f;
        // z must be positive
        z = (rand() / (float)RAND_MAX) * -20.0f - 15.0f;

        memcpy(&buffer[i][0], &x, sizeof(float));
        memcpy(&buffer[i][1], &y, sizeof(float));
        memcpy(&buffer[i][2], &z, sizeof(float));
    }
} 

static void render_loop() {
    process_inputs();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(scene->vao);

    for(unsigned int i = 0; i < 10; i++)
    {
        glm_mat4_identity(scene->model);
        glm_translate(scene->model, cube_positions[i]);
        glm_rotate(scene->model, (float)glfwGetTime() * (i + 1.0f) + 20.0f, (vec4){0.3f, 0.1f, 0.0f, 0.0f});
        scene->shader->setUniformM4F(scene->shader, uniforms.model, scene->model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}

int camera_lesson(void) {
    gen_cube_positions(cube_positions, 10);

    window_manager = init_window_manager();
    window_manager->open_window(window_manager, "Camera", 800, 600);

    window_manager->render(window_manager, render_loop, 0);

    destroy_scene(scene);
    window_manager->close_window(window_manager);

    return 0;
}