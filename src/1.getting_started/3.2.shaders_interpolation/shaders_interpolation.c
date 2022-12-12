#include "1.getting_started/3.2.shaders_interpolation/shaders_interpolation.h"

float maVertices[] = {
    // postitions       // colors
    -0.5f, 0.3f, -1.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.7f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f};

const char *maVertexShaderSource = "#version 460 core\n"
                                   "layout (location = 0) in vec3 aPos;\n"
                                   "layout (location = 1) in vec3 aColor;\n"
                                   "out vec3 vertexColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                   "   vertexColor = aColor;\n"
                                   "}\0";

const char *maFragmentShaderSource = "#version 460 core\n"
                                     "out vec4 FragColor;\n"
                                     "in vec3 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "FragColor = vec4(vertexColor, 1.0);\n"
                                     "}\n";

int more_attributes_lesson(void)
{
    GLFWwindow *window = init_window();
    int success;
    char infoLog[512];

    // 1. compile shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = compile_shader(maVertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(maFragmentShaderSource, GL_FRAGMENT_SHADER);

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

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(maVertices), maVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Must clear before drawing (not after)
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}