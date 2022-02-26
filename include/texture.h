#ifndef TEXTURE_H

#define TEXTURE_H

#include <stdbool.h>
#include "custom_helpers.h"

unsigned int init_texture_2d(const char *image_path, GLint format, GLint internal_format);

#endif