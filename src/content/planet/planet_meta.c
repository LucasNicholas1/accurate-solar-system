#include "planet_meta.h"

#include <stdio.h>

#define PATH_PREFIX ASSETS_DIR "/textures/planets/"
#define PATH_SUFFIX ".jpg"
#define PATH_SIZE 100

static PlanetMeta Create(PlanetType type, int index);
static PlanetMeta CreateBoth(const char* lit_path, const char* dark_path, char storage[2][PATH_SIZE]);
static PlanetMeta CreateDistinct(const char* path, char storage[2][PATH_SIZE]);

PlanetMeta planet_metas[COUNT];
static char paths[COUNT][2][PATH_SIZE];

void InitPlanetMetas() {
    for (int i = 0; i < COUNT; i++) {
        planet_metas[i] = Create((PlanetType) i, i);
    }
}

PlanetMeta Create(PlanetType type, int index) {
    switch (type) {
        case MERCURY:
            return CreateDistinct("mercury", paths[index]);
        case VENUS:
            return CreateDistinct("venus", paths[index]);
        case EARTH:
            return CreateBoth("earth_lit", "earth_dark", paths[index]);
        case MARS:
            return CreateDistinct("mars", paths[index]);
        case JUPITER:
            return CreateDistinct("jupiter", paths[index]);
        default:
            return (PlanetMeta) { 0 };
    }
}

PlanetMeta CreateBoth(const char* lit_path, const char* dark_path, char storage[2][PATH_SIZE]) {
    snprintf(storage[0], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, lit_path);
    snprintf(storage[1], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, dark_path);

    return (PlanetMeta) {
        .lit_path = storage[0],
        .dark_path = storage[1],
    };
}

PlanetMeta CreateDistinct(const char* path, char storage[2][PATH_SIZE]) {
    snprintf(storage[0], PATH_SIZE, PATH_PREFIX "%s" PATH_SUFFIX, path);

    return (PlanetMeta) {
        .lit_path = storage[0],
        .dark_path = storage[0],
    };
}
