#include "1.getting_started/3.6.shaders_exercise3/shaders_exercise3.h"

float vVertices[] = {
    // postitions
    -0.5f, 0.3f, -1.0f,
    0.0f, 0.8f, 0.0f,
    0.7f, 0.5f, 1.0f};

int vert_color_lesson(void)
{
    GLFWwindow *window = init_window();
    shader_t *s = init_shader("./bin/assets/shaders/vert_color.vert", "./bin/assets/shaders/vert_color.frag");

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Must clear before drawing (not after)
        glClear(GL_COLOR_BUFFER_BIT);

        s->use(s);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy_shader(s);

    glfwTerminate();
    return 0;
}
