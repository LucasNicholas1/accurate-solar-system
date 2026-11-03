#ifndef ACCURATE_SOLAR_SYSTEM_PLANET_H
#define ACCURATE_SOLAR_SYSTEM_PLANET_H

#include <glad/glad.h>

typedef struct Planet {
    GLuint vao;
    GLuint vbo;
    GLuint program;
} Planet;

Planet CreatePlanet();
void RenderPlanet(Planet* planet);

#endif //ACCURATE_SOLAR_SYSTEM_PLANET_H
