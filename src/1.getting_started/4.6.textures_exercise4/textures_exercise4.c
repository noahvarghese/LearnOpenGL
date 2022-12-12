#include "1.getting_started/4.6.textures_exercise4/textures_exercise4.h"

float color[] = {
    // (254.0f / 255.0f),
    // (168.0f / 255.0f),
    // 0.0f
    1.0f,
    1.0f,
    1.0f,
};

float rectangleVertices[] = {
    // vertex         // texture coordinate
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f};

unsigned int rectangleIndices[] = {
    0, 1, 3,
    1, 2, 3};

int smiling_box_lesson(void)
{
    GLFWwindow *window = init_window();

    shader_t *s = init_shader("./bin/assets/shaders/smiling_box.vert", "./bin/assets/shaders/smiling_box.frag");

    texture_2d_t *containerTexture = init_texture_2d("./bin/assets/images/container.jpg", GL_RGB, GL_RGB, GL_TEXTURE0);
    texture_2d_t *smileyTexture = init_texture_2d("./bin/assets/images/awesomeface.png", GL_RGBA, GL_RGBA, GL_TEXTURE1);

    unsigned int VAO, VBO, EBO;

    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    float visibility = 0.5f;

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (visibility < 0.98f)
            {
                visibility += 0.005f;
            }
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (visibility > 0.02f)
            {
                visibility -= 0.005f;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s->use(s);
        s->setUniformFloat(s, "visibility", visibility);
        s->setUniformInt(s, "texture0", 0);
        s->setUniformInt(s, "texture1", 1);

        containerTexture->bind(containerTexture);
        smileyTexture->bind(smileyTexture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy_shader(s);
    destroy_texture_2d(containerTexture);
    destroy_texture_2d(smileyTexture);
    glfwTerminate();
    return 0;
}