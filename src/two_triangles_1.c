#include "two_triangles_1.h"

float tt1Vertices[] = {
    // first triangle
    -0.5f, -0.5f, 0.0f,
    -0.0f, -0.5f, 0.0f,
    -0.25f, 0.0f, 0.0f,
    // second triangle
    0.5f, 0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    0.25f, 0.0f, 0.0f};

const char *tt1VertexShaderSource = "#version 460 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

const char *tt1FragmentShaderSource = "#version 460 core\n"
                                      "out vec4 FragColor;\n"
                                      "void main()\n"
                                      "{\n"
                                      "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                      "}\n";
int two_triangles_1_lesson(void)
{
    GLFWwindow *window = init_window();
    int success;
    char infoLog[512];

    // 1. compile shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = compile_shader(tt1VertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(tt1FragmentShaderSource, GL_FRAGMENT_SHADER);

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

    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tt1Vertices), tt1Vertices, GL_STATIC_DRAW);

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
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}