#include "1.getting_started/6.2.coordinate_systems_depth/coordinate_systems_depth.h"

float vertices[] = {
     // vertex            // texture coordinate
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    
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

void process_inputs() {
    if (window_manager->poll_for_key_input(window_manager, GLFW_KEY_ESCAPE))
    {
        window_manager->close_window(window_manager);
    }
}

void gen_cube_positions(vec3 buffer[], int num_cubes) {
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

void render_loop() {
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

int coordinate_lesson_3d(void)
{
    gen_cube_positions(cube_positions, 10);

    window_manager = init_window_manager();
    window_manager->open_window(window_manager, "3D coordinates", 800, 600);

    shader_t *shader = init_shader("./bin/assets/shaders/3d_coordinates.vert", "./bin/assets/shaders/3d_coordinates.frag");
    texture_2d_t *container_texture = init_texture_2d("./bin/assets/images/container.jpg", GL_RGB, GL_RGB, GL_TEXTURE0);

    glEnable(GL_DEPTH_TEST);

    // Setup buffers to render the shapes 
    unsigned int VAO, VBO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture_2d_t *textures[] = {container_texture, NULL};
    scene = init_scene(VAO, textures, shader);

    int width, height;
    window_manager->get_window_dimensions(window_manager, &width, &height);

    glm_perspective(glm_rad(45.0f), (float)(width / height), 0.1f, 100.0f, scene->projection);
    glm_translate(scene->view, (vec3){0.0f, 0.0f, -3.0f});

    texture_2d_t **texture = scene->textures;
    while (*texture)
    {
        (*texture)->bind(*texture);
        ++texture;
    }

    // setup uniforms
    scene->shader->use(scene->shader);
    scene->shader->setUniformInt(scene->shader, uniforms.texture0, 0);
    scene->shader->setUniformM4F(scene->shader, uniforms.view, scene->view);
    scene->shader->setUniformM4F(scene->shader, uniforms.projection, scene->projection);

    window_manager->render(window_manager, render_loop, 0);
    // render_loop();

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &VBO);

    destroy_scene(scene);
    window_manager->close_window(window_manager);
    free_window_manager(window_manager);

    return 0;
}