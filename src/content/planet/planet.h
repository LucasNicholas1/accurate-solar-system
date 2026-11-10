#ifndef ACCURATE_SOLAR_SYSTEM_PLANET_H
#define ACCURATE_SOLAR_SYSTEM_PLANET_H

typedef enum PlanetType PlanetType;
typedef struct Camera Camera;

typedef struct Planet {
    unsigned int vao;
    unsigned int vbo;
    unsigned int lit_tex;
    unsigned int lit_slot;
    unsigned int dark_tex;
    unsigned int dark_slot;
    int vertex_count;
} Planet;

Planet CreatePlanet(PlanetType type);
void RenderPlanet(const Planet* planet, int model_loc, int lit_tex_loc, int dark_tex_loc);
void DisposePlanet(const Planet* planet);

#endif //ACCURATE_SOLAR_SYSTEM_PLANET_H
