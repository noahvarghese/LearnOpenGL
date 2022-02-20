#include "examples/uniforms.h"

const char *uVertexShaderSource = "#version 460 core\n"
                                  "layout (location = 0) in vec3 aPos;\n"
                                  "void main()\n"
                                  "{\n"
                                  "gl_Position = vec4(aPos, 1.0);\n"
                                  "}\n";

const char *uFragShaderSource = "#version 460 core\n"
                                "out vec4 FragColor;\n"
                                "uniform vec4 vertexColor;\n"
                                "void main()\n"
                                "{\n"
                                "FragColor = vertexColor;\n"
                                "}\n";

float uVertices[] = {
    // postitions
    -0.5f, 0.3f, -1.0f,
    0.0f, 0.8f, 0.0f,
    0.7f, 0.5f, 1.0f};

int uniforms_lesson(void)
{
    GLFWwindow *window = init_window();
    int success;
    char infoLog[512];

    // 1. compile shaders
    unsigned int vertexShader;
    unsigned int fragmentShader;

    vertexShader = compile_shader(uVertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = compile_shader(uFragShaderSource, GL_FRAGMENT_SHADER);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(uVertices), uVertices, GL_STATIC_DRAW);

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
        const char *uniformName = "vertexColor";
        int vertexColorLocation = glGetUniformLocation(shaderProgram, uniformName);

        if (vertexColorLocation == -1)
        {
            const char *message = "Failed to get uniform location: ";
            error(str_concat(message, uniformName));
        }

        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.5f, green, 0.5f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}