#include "examples/transformations.h"

float smilingBoxVertices[] = {
    // vertex         // texture coordinate
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f};

unsigned int smilingBoxIndices[] = {
    0, 1, 3,
    1, 2, 3};

int transformation_lesson(void)
{
    mat4 trans;
    glm_mat4_identity(trans);
    glm_rotate(trans, glm_rad(90.0f), (vec3){0.0f, 0.0f, 1.0f});
    glm_scale(trans, (vec3){0.5f, 0.5f, 0.5f});

    GLFWwindow *window = init_window();

    shader *s = init_shader("./bin/assets/shaders/smiling_box.vert", "./bin/assets/shaders/smiling_box.frag");

    unsigned int containerTexture = init_texture_2d("./bin/assets/images/container.jpg", GL_RGB, GL_RGB);
    unsigned int smileyTexture = init_texture_2d("./bin/assets/images/awesomeface.png", GL_RGBA, GL_RGBA);

    unsigned int VAO, VBO, EBO;

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(smilingBoxVertices), smilingBoxVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(smilingBoxIndices), smilingBoxIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    float visibility = 0.5f;
    float change = 0.005f;
    // milliseconds
    int interval = 5;

    struct timeval prevTime;
    gettimeofday(&prevTime, NULL);

    while (!glfwWindowShouldClose(window))
    {
        struct timeval currTime;
        gettimeofday(&currTime, NULL);

        unsigned int diff;
        diff = (unsigned int)(((10000.0 * (currTime.tv_sec - prevTime.tv_sec)) + (currTime.tv_usec - prevTime.tv_usec)) / 10000.0);

        if (diff > interval)
        {
            float t = (float)(diff * (double)change);
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                if ((visibility + t) < 0.99f)
                {
                    visibility += t;
                }
            }
            else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                if ((visibility - t) > 0.01f)
                {
                    visibility -= t;
                }
            }
            prevTime = currTime;
        }

        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s->use(s);
        s->setUniformFloat(s, "visibility", visibility);
        s->setUniformInt(s, "texture0", 0);
        s->setUniformInt(s, "texture1", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, containerTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, smileyTexture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroy_shader(s);
    glfwTerminate();
    return 0;
}
