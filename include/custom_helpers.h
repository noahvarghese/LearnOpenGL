#ifndef CUSTOM_H

#define CUSTOM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow *window);
void error(const char *message);
const char *str_concat(const char *str1, const char *str2);
unsigned int compile_shader(const char *shaderSource, GLenum shaderType);
GLFWwindow *init_window();

#endif