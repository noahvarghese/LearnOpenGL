#include "mandelbrot/mandelbrot.h"

static float vertices[] = {
    // vertex
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
};

static unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};

static scene_t *scene;
static window_manager_t *window_manager;

static void process_inputs() {
  if (window_manager->poll_for_key_input(window_manager, GLFW_KEY_ESCAPE))
  {
    window_manager->close_window(window_manager);
  }
}

static void render_loop() {
  process_inputs();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(scene->vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

int mandelbrot(void)
{
  window_manager = init_window_manager();
  window_manager->open_window(window_manager, "Mandelbrot", 800, 600);

  shader_t *shader = init_shader("./bin/assets/shaders/mandelbrot.vert", "./bin/assets/shaders/mandelbrot.frag");

  // Setup buffers to render the shapes 
  unsigned int VAO, VBO, EBO;

  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  scene = init_scene(VAO, NULL, shader);

  // setup uniforms
  scene->shader->use(scene->shader);

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