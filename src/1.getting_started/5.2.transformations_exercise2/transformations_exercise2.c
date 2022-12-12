#include "1.getting_started/5.2.transformations_exercise2/transformations_exercise2.h"

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
    GLFWwindow *window = init_window();

    shader_t *s = init_shader("./bin/assets/shaders/smiling_box.vert", "./bin/assets/shaders/smiling_box.frag");

    texture_2d_t *containerTexture = init_texture_2d("./bin/assets/images/container.jpg", GL_RGB, GL_RGB, GL_TEXTURE0);
    texture_2d_t *smileyTexture = init_texture_2d("./bin/assets/images/awesomeface.png", GL_RGBA, GL_RGBA, GL_TEXTURE1);

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

        mat4 transform;
        glm_mat4_identity(transform);
        glm_translate(transform, (vec3){0.5f, -0.5f, 0.0f});
        glm_rotate(transform, (float)glfwGetTime(), (vec3){0.0f, 0.0f, 1.0f});

        s->setUniformM4F(s, "transform", transform);

        containerTexture->bind(containerTexture);
        smileyTexture->bind(smileyTexture);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glm_mat4_identity(transform);
        glm_translate(transform, (vec3){-0.5f, 0.5f, 0.0f});
        vec3 scale = {0.0f, 0.0f, 0.0f};
        glm_vec3_scale((vec3){0.5f, 0.5f, 1.0f}, (float)fabs(sin(glfwGetTime())) + 0.25f, scale);
        glm_scale(transform, scale);
        s->setUniformM4F(s, "transform", transform);
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
