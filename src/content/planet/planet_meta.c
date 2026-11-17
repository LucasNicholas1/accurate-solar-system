#include "planet_meta.h"

#include <stdio.h>

#define PATH_PREFIX ASSETS_DIR "textures/planets/"
#define PATH_SUFFIX ".dds"
#define PATH_SIZE 100

static PlanetMeta Create(PlanetType type, int index);
static PlanetMeta CreateBoth(const char* lit_path, const char* dark_path, char storage[2][PATH_SIZE], const char* cspice_target);
static PlanetMeta CreateDistinct(const char* path, char storage[2][PATH_SIZE], const char* cspice_target);

PlanetMeta planet_metas[PLANET_TYPE_COUNT];
static char paths[PLANET_TYPE_COUNT][2][PATH_SIZE];

void InitPlanetMetas() {
    for (int i = 0; i < PLANET_TYPE_COUNT; i++) {
        planet_metas[i] = Create((PlanetType) i, i);
    }
}

PlanetMeta Create(PlanetType type, int index) {
    switch (type) {
        case MERCURY:
            return CreateDistinct("mercury", paths[index], "MERCURY");
        case VENUS:
            return CreateDistinct("venus", paths[index], "VENUS");
        case EARTH:
            return CreateBoth("earth_lit", "earth_dark", paths[index], "EARTH");
        case MARS:
            return CreateDistinct("mars", paths[index], "MARS");
        case JUPITER:
            return CreateDistinct("jupiter", paths[index], "JUPITER");
        case SATURN:
            return CreateDistinct("saturn", paths[index], "SATURN");
        case URANUS:
            return CreateDistinct("uranus", paths[index], "URANUS");
        case NEPTUNE:
            return CreateDistinct("neptune", paths[index], "NEPTUNE");
        default:
            return (PlanetMeta) { 0 };
    }
}

PlanetMeta CreateBoth(const char* lit_path, const char* dark_path, char storage[2][PATH_SIZE], const char* cspice_target) {
    snprintf(storage[0], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, lit_path);
    snprintf(storage[1], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, dark_path);

    return (PlanetMeta) {
        .lit_path = storage[0],
        .dark_path = storage[1],
        .cspice_target = cspice_target,
    };
}

PlanetMeta CreateDistinct(const char* path, char storage[2][PATH_SIZE], const char* cspice_target) {
    snprintf(storage[0], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, path);

    return (PlanetMeta) {
        .lit_path = storage[0],
        .dark_path = storage[0],
        .cspice_target = cspice_target,
    };
}
