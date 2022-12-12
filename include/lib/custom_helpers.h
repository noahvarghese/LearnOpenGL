#ifndef CUSTOM_H

#define CUSTOM_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/std_utils.h"

void process_input(GLFWwindow *window);
unsigned int compile_shader(const char *shaderSource, GLenum shaderType);
GLFWwindow *init_window();

#endif