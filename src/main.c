#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *open_window(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Noah Learns OpenGL", NULL, NULL);
    return window;
}

int init_glad(void)
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        fprintf(stdout, "ESCAPE PRESSED\n");
    }
}

void render_loop(GLFWwindow *window)
{
    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

int main(void)
{
    printf("Hello, World\n");

    if (!glfwInit())
    {
        fprintf(stderr, "Unable to init glfw\n");
        exit(1);
    }

    GLFWwindow *window = open_window();

    if (window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        exit(1);
    }

    glfwMakeContextCurrent(window);

    if (init_glad() < 0)
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        exit(1);
    }

    framebuffer_size_callback(window, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    render_loop(window);

    glfwTerminate();
    return 0;
}