#include "planets.h"

#include "planet_meta.h"
#include "../camera/camera.h"
#include "../../tools/program.h"
#include <glad/glad.h>

#define PLANET_COUNT 1

typedef struct Planets {
    Camera* camera;
    GLuint program;
    Planet arr[PLANET_COUNT];
    GLint proj_loc;
    GLint view_loc;
    GLint view_pos_loc;
    GLint model_loc;
    GLint lit_tex_loc;
    GLint dark_tex_loc;
} Planets;

static Planets planets;

void InitPlanets(Camera* camera) {
    planets.camera = camera;
    planets.program = CreateProgram(ASSETS_DIR "/shaders/planet.vert", ASSETS_DIR "/shaders/planet.frag");

    planets.proj_loc = glGetUniformLocation(planets.program, "uProj");
    planets.view_loc = glGetUniformLocation(planets.program, "uView");
    planets.view_pos_loc = glGetUniformLocation(planets.program, "uViewPos");
    planets.model_loc = glGetUniformLocation(planets.program, "uModel");
    planets.lit_tex_loc = glGetUniformLocation(planets.program, "uLitTexture");
    planets.dark_tex_loc = glGetUniformLocation(planets.program, "uDarkTexture");

    InitPlanetMetas();

    // Make sure PLANET_COUNT planets are defined below
    planets.arr[0] = CreatePlanet(EARTH);
}

void UpdatePlanets(float delta) {
    glUseProgram(planets.program);

    glUniformMatrix4fv(planets.proj_loc, 1, GL_FALSE, (const float*) planets.camera->proj);
    glUniformMatrix4fv(planets.view_loc, 1, GL_FALSE, (const float*) planets.camera->view);
    glUniform3f(planets.view_pos_loc, planets.camera->pos[0], planets.camera->pos[1], planets.camera->pos[2]);

    for (int i = 0; i < PLANET_COUNT; i++) {
        RenderPlanet(&planets.arr[i], planets.model_loc, planets.lit_tex_loc, planets.dark_tex_loc);
    }
}

void DisposePlanets() {
    for (int i = 0; i < PLANET_COUNT; i++) {
        DisposePlanet(&planets.arr[i]);
    }

    glDeleteProgram(planets.program);
}
