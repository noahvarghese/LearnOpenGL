#include "examples/two_triangles_2.h"

const char *tt2VertexShaderSource = "#version 460 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

const char *tt2FragmentShaderSource = "#version 460 core\n"
                                      "out vec4 FragColor;\n"
                                      "void main()\n"
                                      "{\n"
                                      "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                      "}\n";
int two_triangles_2_lesson(void)
{
    float triangle1[] = {
        -0.5f,
        -0.5f,
        0.0f,
        -0.0f,
        -0.5f,
        0.0f,
        -0.25f,
        0.0f,
        0.0f,
    };

    float triangle2[] = {
        0.5f, 0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.25f, 0.0f, 0.0f};

    GLFWwindow *window = init_window();

    int success;
    char infoLog[512];

    // 1. compile shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = compile_shader(tt2VertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(tt2FragmentShaderSource, GL_FRAGMENT_SHADER);

    // 2. create program with shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        const char *message = str_concat("Shader compilation failed\n", infoLog);
        error(message);
    }

    // 3. clearnup shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAOs[2], VBOs[2];

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Must clear before drawing (not after)
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}