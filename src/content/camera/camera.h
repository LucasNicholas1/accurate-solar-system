#ifndef ACCURATE_SOLAR_SYSTEM_CAMERA_H
#define ACCURATE_SOLAR_SYSTEM_CAMERA_H

#include <cglm/vec3.h>

typedef struct GLFWwindow GLFWwindow;

typedef struct Camera {
    mat4 proj;
    mat4 view;
    vec3 pos;
    vec3 dir;
    float fov;
    float yaw;
    float pitch;
    GLFWwindow* window;
} Camera;

Camera CreateCamera(float fov, GLFWwindow* window);
void UpdateCamera(Camera* camera, float delta);
void ResizeCamera(Camera* camera, int width, int height);
void RotateCamera(Camera* camera, float x_delta, float y_delta);

#endif //ACCURATE_SOLAR_SYSTEM_CAMERA_H
