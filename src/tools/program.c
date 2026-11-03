#include "../program.h"

#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

static GLuint CreateShader(const char* path, GLint type) {
    GLuint shader = glCreateShader(type);

    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Failed to open shader file: %s\n", path);
        return 0;
    }

    fseek(file, 0L, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "Failed to obtain contents of shader file: %s\n", path);
        return 0;
    }

    size_t read_bytes = fread(buffer, 1, size, file);
    buffer[read_bytes] = '\0';
    fclose(file);

    glShaderSource(shader, 1, (const char* const*) &buffer, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        constexpr GLsizei log_size = 512;
        char log[log_size];
        glGetShaderInfoLog(shader, log_size, nullptr, log);
        fprintf(stderr, "Failed to compile shader %s:\n", path);
        fprintf(stderr, "%s", log);
    }

    free(buffer);
    return shader;
}

GLuint CreateProgram(const char* vert_path, const char* frag_path) {
    GLuint vert = CreateShader(vert_path, GL_VERTEX_SHADER);
    GLuint frag = CreateShader(frag_path, GL_FRAGMENT_SHADER);

    if (!vert || !frag) {
        glDeleteShader(vert);
        glDeleteShader(frag);
        return 0;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glLinkProgram(program);
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        constexpr GLsizei log_size = 512;
        char log[log_size];
        glGetProgramInfoLog(program, log_size, nullptr, log);
        fprintf(stderr, "Failed to link program: %s", log);
    }

    glDetachShader(program, vert);
    glDetachShader(program, frag);
    glDeleteShader(vert);
    glDeleteShader(frag);

    if (!success) {
        glDeleteProgram(program);
        return 0;
    }

    return program;
}