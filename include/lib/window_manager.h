#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils/std_utils.h"
#include "utils/string_utils.h"

// OpenGL versions
#define GLFW_CONTEXT_VERSION_MAJOR_VALUE 4
#define GLFW_CONTEXT_VERSION_MINOR_VALUE 6
#define GLFW_OPENGL_PROFILE_VALUE GLFW_OPENGL_CORE_PROFILE

typedef enum {
    release = GLFW_RELEASE,
    press = GLFW_PRESS,
    // repeat = GLFW_REPEAT,
} action_e;

/**
 * The void pointer is to avoid exposing GLFW details to the consumer
 */
// typedef void (*on_key_input_f)(void *_, int key, int scancode, action_e action, int mods);

typedef struct window_manager_t{
    GLFWwindow *window;
    void (*close_window)(struct window_manager_t *self);
    void (*open_window)(struct window_manager_t *self, const char *title, int width, int height);
    void (*resize_window)(struct window_manager_t *self, int width, int height);
    action_e (*poll_for_key_input)(struct window_manager_t *self, int key);
    void (*get_window_dimensions)(struct window_manager_t *self, int *width, int *height);
    /**
     * Trigger the render loop
     */
    void (*render)(struct window_manager_t *self, void (*loop)(), int fps);
    // void (*set_key_input_callback)(struct window_manager_t *self, on_key_input_f callback);
} window_manager_t;

// window_manager_t *init_window(const char *title, int width, int height, on_key_input_f callback);
window_manager_t *init_window_manager();
void free_window_manager(window_manager_t *self);

#endif