#include "fetcher.h"

#include <assert.h>
#include <SpiceUsr.h>
#include <stdio.h>

static SpiceDouble et;

#define SCALE 0.0000001f

void InitFetcher() {
    // For position
    furnsh_c(KERNEL_DIR "naif0012.tls");
    furnsh_c(KERNEL_DIR "de440s.bsp");

    // For radius
    furnsh_c(KERNEL_DIR "pck00011.tpc");

    str2et_c("2026 NOV 13 12:00:00", &et);
}

void DisposeFetcher() {
    unload_c(KERNEL_DIR "naif0012.tls");
    unload_c(KERNEL_DIR "de440s.bsp");
    unload_c(KERNEL_DIR "pck00011.tpc");
}

void FetchPlanetPosition(const char* target, vec3 pos) {
    SpiceDouble spice_pos[3];
    SpiceDouble lt; // Light time

    char target_barycenter[64];
    snprintf(target_barycenter, sizeof(target_barycenter), "%s BARYCENTER", target);

    spkpos_c(
        target_barycenter,
        et,
        "ECLIPJ2000",
        "NONE",
        "SUN",
        spice_pos,
        &lt
    );

    pos[0] = (float) spice_pos[0] * SCALE;
    pos[1] = (float) spice_pos[2] * SCALE;
    pos[2] = (float) spice_pos[1] * SCALE;

    // printf("Fetched position: %f %f %f\n", pos[0], pos[1], pos[2]);
}

void FetchPlanetRadii(const char* target, vec3 radii) {
    SpiceInt dim;
    SpiceDouble spice_radii[3];

    bodvrd_c(target, "RADII", 3, &dim, spice_radii);
    assert(dim == 3);

    radii[0] = (float) spice_radii[0] * SCALE * 1.0f;
    radii[1] = (float) spice_radii[2] * SCALE * 1.0f;
    radii[2] = (float) spice_radii[1] * SCALE * 1.0f;

    // printf("Fetched radii: %f %f %f\n", radii[0], radii[1], radii[2]);
}
