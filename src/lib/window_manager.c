#include "lib/window_manager.h"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void resize_window(window_manager_t *self, int width, int height) {
    framebuffer_size_callback(self->window, width, height);
    glfwSetFramebufferSizeCallback(self->window, &framebuffer_size_callback);
}

static action_e poll_for_key_input(window_manager_t *self, int key) {
    action_e action;
    action = glfwGetKey(self->window, key);
    return action;
}

static void close_window(window_manager_t *self) {
    glfwSetWindowShouldClose(self->window, true);
}

static void open_window(window_manager_t *self,  const char *title, int width, int height) {
    // TODO: Maybe implement managing multiple windows?
    if (self->window != NULL)
    {
        error("Must close current window before opening a new one");
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_CONTEXT_VERSION_MAJOR_VALUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_CONTEXT_VERSION_MINOR_VALUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_PROFILE_VALUE);

    self->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (self->window == NULL)
    {
        error("Failed to create GLFW window\nPlease reboot and try again.");
    }

    glfwMakeContextCurrent(self->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        error("Failed to initialize GLAD");
    }
    
    resize_window(self, width, height);
}

static void get_window_dimensions(window_manager_t *self, int *width, int *height) {
    glfwGetWindowSize(self->window, width, height);
}

static void render(window_manager_t *self, void (*loop)(), int fps_lock) {
    int interval;
    unsigned int diff;
    struct timeval prev_time, curr_time;

    if (fps_lock)
    {
        interval = 1000 / fps_lock; // milliseconds divided by desired frames per second
        gettimeofday(&prev_time, NULL);
    }

    while(!glfwWindowShouldClose(self->window)) {
        if (fps_lock)
        {
            gettimeofday(&curr_time, NULL);
            diff = (unsigned int)(((10000.0 * (curr_time.tv_sec - prev_time.tv_sec)) + (curr_time.tv_usec - prev_time.tv_usec)) / 10000.0);

            if (diff > interval)
            {
                loop();
                glfwSwapBuffers(self->window);
                glfwPollEvents();
            }
        }
        else
        {
            loop();
            glfwSwapBuffers(self->window);
            glfwPollEvents();
        }
    }
}

// static void set_key_input_callback(window_manager_t *self, on_key_input_f on_key_input) {
//     glfwSetKeyCallback(self->window, (GLFWkeyfun)on_key_input);
// }

// window_manager_t *init_window(const char *title, int width, int height, on_key_input_f on_key_input) {
window_manager_t *init_window_manager()
{
    if (!glfwInit())
    {
        error("Unable to init glfw");
    }

    window_manager_t *self;

    self = (window_manager_t *)malloc(sizeof(window_manager_t));
    if (self == NULL)
    {
        error("Unable to allocate memory for window");
    }

    self->poll_for_key_input = poll_for_key_input;
    self->resize_window = resize_window;
    self->close_window = close_window;
    self->open_window = open_window;
    self->get_window_dimensions = get_window_dimensions;
    self->render = render;
    self->window = NULL;
    // self->set_key_input_callback = set_key_input_callback;

    // set_key_input_callback(self, on_key_input);

    return self;
}

void free_window_manager(window_manager_t *self) {
    glfwDestroyWindow(self->window);
    glfwTerminate();
    free(self);
}