#include "planets.h"

#include "sphere.h"
#include "fetcher.h"
#include "planet_meta.h"
#include "../camera/camera.h"
#include "../../tools/program.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#define PLANET_COUNT PLANET_TYPE_COUNT

typedef struct Planets {
    Camera* camera;
    GLuint vbo;
    GLuint program;
    Planet arr[PLANET_COUNT];
    int vertex_count;
    GLint proj_loc;
    GLint view_loc;
    GLint view_pos_loc;
    GLint frame_size_loc;
    GLint model_loc;
    GLint lit_tex_loc;
    GLint dark_tex_loc;
    GLint bin_tex_loc;
} Planets;

static Planets planets;

static GLuint createVBO(int res);

void InitPlanets(Camera* camera) {
    planets.camera = camera;
    planets.program = CreateProgram(ASSETS_DIR "shaders/planet.vert", ASSETS_DIR "shaders/planet.frag");

    planets.proj_loc = glGetUniformLocation(planets.program, "uProj");
    planets.view_loc = glGetUniformLocation(planets.program, "uView");
    planets.view_pos_loc = glGetUniformLocation(planets.program, "uViewPos");
    planets.frame_size_loc = glGetUniformLocation(planets.program, "uFrameSize");
    planets.model_loc = glGetUniformLocation(planets.program, "uModel");
    planets.lit_tex_loc = glGetUniformLocation(planets.program, "uLitTexture");
    planets.dark_tex_loc = glGetUniformLocation(planets.program, "uDarkTexture");
    planets.bin_tex_loc = glGetUniformLocation(planets.program, "uBinaryTexture");

    InitPlanetMetas();
    InitFetcher();

    constexpr int res = 20;
    planets.vbo = createVBO(res);
    planets.vertex_count = GetSphereComponentCount(res);

    // Make sure PLANET_COUNT planets are defined below
    for (int i = 0; i < PLANET_COUNT; i++) {
        planets.arr[i] = CreatePlanet(i, planets.vbo);
    }
}

static GLuint createVBO(int res) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[GetSphereComponentCount(res)];
    GenerateSphere(res, vertices);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) sizeof(vertices), vertices, GL_STATIC_DRAW);

    return vbo;
}

void UpdatePlanets(float delta) {
    glUseProgram(planets.program);

    glUniformMatrix4fv(planets.proj_loc, 1, GL_FALSE, (const float*) planets.camera->proj);
    glUniformMatrix4fv(planets.view_loc, 1, GL_FALSE, (const float*) planets.camera->view);
    glUniform3f(planets.view_pos_loc, planets.camera->pos[0], planets.camera->pos[1], planets.camera->pos[2]);

    int width, height;
    glfwGetFramebufferSize(planets.camera->window, &width, &height);
    glUniform2f(planets.frame_size_loc, (float) width, (float) height);

    for (int i = 0; i < PLANET_COUNT; i++) {
        RenderPlanet(&planets.arr[i], planets.vertex_count, planets.model_loc, planets.lit_tex_loc, planets.dark_tex_loc, planets.bin_tex_loc);
    }
}

void DisposePlanets() {
    DisposeFetcher();

    for (int i = 0; i < PLANET_COUNT; i++) {
        DisposePlanet(&planets.arr[i]);
    }

    glDeleteBuffers(1, &planets.vbo);
    glDeleteProgram(planets.program);
}
