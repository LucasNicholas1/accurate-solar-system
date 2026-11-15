#ifndef ACCURATE_SOLAR_SYSTEM_FETCHER_H
#define ACCURATE_SOLAR_SYSTEM_FETCHER_H

#include <cglm/vec3.h>

void InitFetcher();
void DisposeFetcher();
void FetchPlanetPosition(const char* target, vec3 pos);
void FetchPlanetRadii(const char* target, vec3 radii);

#endif //ACCURATE_SOLAR_SYSTEM_FETCHER_H
