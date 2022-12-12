#include "1.getting_started/3.5.shaders_exercise2/shaders_exercise2.h"

float hoVertices[] = {
    // postitions
    -0.5f, 0.3f, -1.0f,
    0.0f, 0.8f, 0.0f,
    0.7f, 0.5f, 1.0f};

int horizontal_offset_lesson(void)
{
    GLFWwindow *window = init_window();
    shader_t *s = init_shader("./bin/assets/shaders/horizontal_offset.vert", "./bin/assets/shaders/horizontal_offset.frag");

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hoVertices), hoVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Must clear before drawing (not after)
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();
        float green = (sin(time) / 2.0f) + 0.5f;

        s->use(s);
        s->setUniformV4F(s, "vertexColor", 0.5f, green, 0.5f, 1.0f);
        s->setUniformFloat(s, "horizontalOffset", 0.25f);

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
