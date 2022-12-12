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

void render_loop() {
    process_inputs();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm_rotate(scene->model, 0.05f, (vec4){0.3f, 0.1f, 0.0f, 0.0f});
    // glm_rotate(scene->model, (float)glfwGetTime(), (vec4){0.3f, 0.1f, 0.0f, 0.0f});

    scene->shader->use(scene->shader);
    scene->shader->setUniformM4F(scene->shader, uniforms.model, scene->model);

    texture_2d_t **texture = scene->textures;
    while (*texture)
    {
        (*texture)->bind(*texture);
        ++texture;
    }

    glBindVertexArray(scene->vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

int coordinate_lesson_3d(void)
{
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

    glm_translate(scene->view, (vec3){0.0f, 0.0f, -3.0f});
    glm_perspective(glm_rad(45.0f), (float)(width / height), 0.1f, 100.0f, scene->projection);

    // setup uniforms
    shader->use(shader);
    shader->setUniformInt(shader, uniforms.texture0, 0);
    shader->setUniformM4F(shader, uniforms.model, scene->model);
    shader->setUniformM4F(shader, uniforms.view, scene->view);
    shader->setUniformM4F(shader, uniforms.projection, scene->projection);

    window_manager->render(window_manager, render_loop, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &VBO);

    destroy_scene(scene);
    window_manager->close_window(window_manager);
    free_window_manager(window_manager);

    return 0;
}