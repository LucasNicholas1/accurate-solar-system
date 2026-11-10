#include "sphere.h"

#include <math.h>

static constexpr float PI = 3.1415926f;
static constexpr float TAU = PI * 2.0f;
static constexpr float RADIUS = 0.5f;

int GetSphereVertexCount(int res) {
    return 12 * res * (res - 1);
}

int GetSphereComponentCount(int res) {
    return GetSphereVertexCount(res) * 8;
}

void GenerateSphere(int res, float* vertices) {
    int lon_res = res * 2;
    int index = 0;

    for (int i = 0; i < res; i++) {
        for (int j = 0; j < lon_res; j++) {
            float theta_a = (float) i / (float) res * PI;
            float theta_b = (float) (i + 1) / (float) res * PI;

            float phi_a = (float) j / (float) lon_res * TAU;
            float phi_b = (float) (j + 1) / (float) lon_res * TAU;

            float points[4][3] = {
                {
                    sinf(theta_a) * cosf(phi_a) * RADIUS,
                    cosf(theta_a) * RADIUS,
                    sinf(theta_a) * sinf(phi_a) * RADIUS
                },
                {
                    sinf(theta_a) * cosf(phi_b) * RADIUS,
                    cosf(theta_a) * RADIUS,
                    sinf(theta_a) * sinf(phi_b) * RADIUS
                },
                {
                    sinf(theta_b) * cosf(phi_a) * RADIUS,
                    cosf(theta_b) * RADIUS,
                    sinf(theta_b) * sinf(phi_a) * RADIUS
                },
                {
                    sinf(theta_b) * cosf(phi_b) * RADIUS,
                    cosf(theta_b) * RADIUS,
                    sinf(theta_b) * sinf(phi_b) * RADIUS
                }
            };

            float uvs[4][2] = {
                { 1.0f - (float) j / lon_res,       1.0f - (float) i / res },
                { 1.0f - (float) (j + 1) / lon_res, 1.0f - (float) i / res },
                { 1.0f - (float) j / lon_res,       1.0f - (float) (i + 1) / res },
                { 1.0f - (float) (j + 1) / lon_res, 1.0f - (float) (i + 1) / res }
            };

            if (i > 0) {
                for (int k = 0; k < 3; k++) {
                    constexpr int order[] = { 0, 1, 2 };
                    int point = order[k];

                    for (int l = 0; l < 3; l++) {
                        vertices[index++] = points[point][l];
                    }

                    for (int l = 0; l < 3; l++) {
                        vertices[index++] = points[point][l] / RADIUS;
                    }

                    for (int l = 0; l < 2; l++) {
                        vertices[index++] = uvs[point][l];
                    }
                }
            }

            if (i < res - 1) {
                for (int k = 0; k < 3; k++) {
                    constexpr int order[] = { 1, 3, 2 };
                    int point = order[k];

                    for (int l = 0; l < 3; l++) {
                        vertices[index++] = points[point][l];
                    }

                    for (int l = 0; l < 3; l++) {
                        vertices[index++] = points[point][l] / RADIUS;
                    }

                    for (int l = 0; l < 2; l++) {
                        vertices[index++] = uvs[point][l];
                    }
                }
            }
        }
    }
}