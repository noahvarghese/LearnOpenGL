#include "examples/rectangle.h"

const char *rVertexShaderSource = "#version 460 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                  "}\0";

const char *rFragmentShaderSource = "#version 460 core\n"
                                    "out vec4 FragColor;\n"
                                    "void main()\n"
                                    "{\n"
                                    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                    "}\n";

float rVertices[] = {
    0.5f,
    0.5f,
    0.0f,
    0.5f,
    -0.5f,
    0.0f,
    -0.5f,
    -0.5f,
    0.0f,
    -0.5f,
    0.5f,
    0.0f,
};

unsigned int rIndices[] = {
    0, 1, 3,
    1, 2, 3};

int rectangle_lesson(void)
{
    GLFWwindow *window = init_window();

    int success;
    char infoLog[512];

    // 1. compile shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = compile_shader(rVertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(rFragmentShaderSource, GL_FRAGMENT_SHADER);

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
        print_error(message);
    }

    // 3. clearnup shader resources
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VAO, VBO, EBO;

    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rVertices), rVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rIndices), rIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Must clear before drawing (not after)
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}