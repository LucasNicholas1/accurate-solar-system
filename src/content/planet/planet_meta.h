#ifndef ACCURATE_SOLAR_SYSTEM_PLANET_META_H
#define ACCURATE_SOLAR_SYSTEM_PLANET_META_H

typedef enum PlanetType {
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE,
    PLANET_TYPE_COUNT,
} PlanetType;

typedef struct PlanetMeta {
    const char* lit_path;
    const char* dark_path;
    const char* cspice_target;
} PlanetMeta;

extern PlanetMeta planet_metas[];

void InitPlanetMetas();

#endif //ACCURATE_SOLAR_SYSTEM_PLANET_META_H
