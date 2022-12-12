#include "lib/texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#endif

static void bind(texture_2d_t *self) {
    glActiveTexture(self->texture_unit);
    glBindTexture(GL_TEXTURE_2D, self->id);
}

texture_2d_t *init_texture_2d(const char *image_path, GLint format, GLint internal_format, GLuint texture)
{
    texture_2d_t *self;
    self = (texture_2d_t *)malloc(sizeof(texture_2d_t));
    if (self == NULL)
    {
        error("Unable to allocate memory for window");
    }

    self->texture_unit = texture;
    self->bind = bind;

    int width, height, numberOfChannels;
    unsigned char *data;

    data = stbi_load(image_path, &width, &height, &numberOfChannels, 0);

    if (data == NULL)
    {
        error("Unable to read file");
    }

    // 1. Create 1 texture
    glGenTextures(1, &self->id);
    glBindTexture(GL_TEXTURE_2D, self->id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, internal_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return self;
}

void destroy_texture_2d(texture_2d_t *self) {
    free(self);
}