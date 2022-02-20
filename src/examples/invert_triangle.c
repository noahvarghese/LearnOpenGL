#include "examples/invert_triangle.h"

float itVertices[] = {
    // postitions
    -0.5f, 0.3f, -1.0f,
    0.0f, 0.8f, 0.0f,
    0.7f, 0.5f, 1.0f};

int invert_triangle_lesson(void)
{
    const char *uniformName = "vertexColor";
    GLFWwindow *window = init_window();
    shader *s = init_shader("./src/shaders/invert_triangle.vert", "./src/shaders/invert_triangle.frag");

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(itVertices), itVertices, GL_STATIC_DRAW);

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
        s->setUniformV4F(s, uniformName, 0.5f, green, 0.5f, 1.0f);

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