#include "planet.h"

#include "planet_meta.h"
#include "sphere.h"
#include "../camera/camera.h"
#include "../../tools/texture.h"
#include <glad/glad.h>
#include <cglm/cglm.h>

Planet CreatePlanet(PlanetType type) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    constexpr int res = 64;
    float vertices[GetSphereComponentCount(res)];
    GenerateSphere(res, vertices);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));

    GLuint lit_slot;
    GLuint lit_tex = LoadTexture(planet_metas[type].lit_path, &lit_slot);

    GLuint dark_slot = lit_slot;
    GLuint dark_tex = lit_tex;

    if (planet_metas[type].lit_path != planet_metas[type].dark_path) {
        dark_tex = LoadTexture(planet_metas[type].dark_path, &dark_slot);
    }

    int vertex_count = GetSphereVertexCount(res);

    return (Planet) {
        .vao = vao,
        .vbo = vbo,
        .lit_tex = lit_tex,
        .lit_slot = lit_slot,
        .dark_tex = dark_tex,
        .dark_slot = dark_slot,
        .vertex_count = vertex_count,
    };
}

void RenderPlanet(const Planet* planet, GLint model_loc, GLint lit_tex_loc, GLint dark_tex_loc) {
    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_rotate(model, glm_rad(23.5f), (vec3) { 0.0f, 0.0f, 1.0f });
    glUniformMatrix4fv(model_loc, 1, GL_FALSE, (const float*) model);

    glUniform1i(lit_tex_loc, (GLint) planet->lit_slot);
    glUniform1i(dark_tex_loc, (GLint) planet->dark_slot);

    glBindVertexArray(planet->vao);
    glDrawArrays(GL_TRIANGLES, 0, planet->vertex_count);
}

void DisposePlanet(const Planet* planet) {
    glDeleteVertexArrays(1, &planet->vao);
    glDeleteBuffers(1, &planet->vbo);

    if (planet->lit_tex != planet->dark_tex) {
        glDeleteTextures(1, &planet->dark_tex);
    }
    glDeleteTextures(1, &planet->lit_tex);
}
