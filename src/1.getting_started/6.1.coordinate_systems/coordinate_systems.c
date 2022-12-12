#include "1.getting_started/6.1.coordinate_systems/coordinate_systems.h"

float rVert[] = {
    // vertex         // texture coordinate
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f};

unsigned int rInd[] = {
    0, 1, 3,
    1, 2, 3};

int coordinate_lesson_2d(void)
{
    GLFWwindow *window = init_window();

    shader_t *s = init_shader("./bin/assets/shaders/2d_coordinates.vert", "./bin/assets/shaders/2d_coordinates.frag");

    texture_2d_t *containerTexture = init_texture_2d("./bin/assets/images/container.jpg", GL_RGB, GL_RGB, GL_TEXTURE0);
    texture_2d_t *smileyTexture = init_texture_2d("./bin/assets/images/awesomeface.png", GL_RGBA, GL_RGBA, GL_TEXTURE1);

    unsigned int VAO, VBO, EBO;

    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rVert), rVert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rInd), rInd, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    s->use(s);
    s->setUniformInt(s, "texture1", 1);
    s->setUniformInt(s, "texture0", 0);

    // make it 3d
    mat4 model, view, projection;

    glm_mat4_identity(model);
    glm_mat4_identity(view);
    glm_mat4_identity(projection);

    // rotate model to face 'up'
    glm_rotate(model, glm_rad(-55.0f), (vec3){1.0f, 0.0f, 0.0f});

    // move scene backwards
    glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

    int width, height;

    glfwGetWindowSize(window, &width, &height);

    // set camera
    glm_perspective(glm_rad(45.0f), (float)(width / height), 0.1f, 100.0f, projection);

    s->setUniformM4F(s, "model", model);
    s->setUniformM4F(s, "view", view);
    s->setUniformM4F(s, "projection", projection);

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