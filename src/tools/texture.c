#include "texture.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <assert.h>

static GLuint slot_idx = 0;

unsigned int LoadTexture(const char* path, GLuint* slot) {
    int width, height, channels;

    stbi_set_flip_vertically_on_load(1);

    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    if (!data) {
        fprintf(stderr, "Failed to load texture %s\n", path);
        return 0;
    }

    assert(channels == 3 || channels == 4 && "Channels of texture must be RGBA");
    GLenum format = channels == 3 ? GL_RGB : GL_RGBA;

    GLuint texture;
    glGenTextures(1, &texture);

    *slot = slot_idx++;
    glActiveTexture(GL_TEXTURE0 + *slot);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return texture;
}

void DisposeTexture(unsigned int texture) {
    glDeleteTextures(1, &texture);
}