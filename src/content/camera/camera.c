#include "camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

static void Reproject(Camera* camera);
static void Move(Camera* camera, float delta);

Camera CreateCamera(float fov, GLFWwindow* window) {
    Camera camera;
    camera.fov = glm_rad(fov);
    camera.window = window;

    Reproject(&camera);
    glm_mat4_identity(camera.view);

    glm_vec3_copy((vec3) { 0.0f, 0.0f, 3.0f }, camera.pos);
    glm_vec3_copy((vec3) { 0.0f, 0.0f, 1.0f }, camera.dir);

    camera.yaw = 0.0f;
    camera.pitch = 0.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return camera;
}

void Reproject(Camera* camera) {
    int width, height;
    glfwGetFramebufferSize(camera->window, &width, &height);
    float aspect = (float) width / (float) height;
    glm_perspective(camera->fov, aspect, 0.01f, 1000.0f, camera->proj);
}

void UpdateCamera(Camera* camera, float delta) {
    float yaw_rad = glm_rad(camera->yaw);
    float pitch_rad = glm_rad(camera->pitch);

    glm_vec3_copy((vec3) {
        cosf(pitch_rad) * sinf(yaw_rad),
        sinf(pitch_rad),
        -cosf(pitch_rad) * cosf(yaw_rad),
    }, camera->dir);

    Move(camera, delta);

    vec3 center;
    glm_vec3_add(camera->pos, camera->dir, center);
    glm_lookat(camera->pos, center, (vec3) { 0.0f, 1.0f, 0.0f }, camera->view);
}

void ResizeCamera(Camera* camera, [[maybe_unused]] int width, [[maybe_unused]] int height) {
    Reproject(camera);
}

void RotateCamera(Camera* camera, float x_delta, float y_delta) {
    constexpr float sens = 0.075f;
    camera->yaw += x_delta * sens;
    camera->pitch -= y_delta * sens;
    camera->pitch = glm_clamp(camera->pitch, -89.999f, 89.999f);
}

void Move(Camera* camera, float delta) {
    delta *= glfwGetKey(camera->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 0.2f : 0.05f;

    bool d = glfwGetKey(camera->window, GLFW_KEY_D) == GLFW_PRESS;
    bool a = glfwGetKey(camera->window, GLFW_KEY_A) == GLFW_PRESS;
    bool w = glfwGetKey(camera->window, GLFW_KEY_W) == GLFW_PRESS;
    bool s = glfwGetKey(camera->window, GLFW_KEY_S) == GLFW_PRESS;
    bool e = glfwGetKey(camera->window, GLFW_KEY_E) == GLFW_PRESS;
    bool q = glfwGetKey(camera->window, GLFW_KEY_Q) == GLFW_PRESS;

    float right_speed = (float) (d - a) * delta;
    float forward_speed = (float) (w - s) * delta;
    float up_speed = (float) (e - q) * delta;

    vec3 forward;
    glm_vec3_copy(camera->dir, forward);
    vec3 right;
    glm_vec3_cross(forward, (vec3) { 0.0f, 1.0f, 0.0f }, right);
    glm_normalize(right);
    vec3 up;
    glm_vec3_cross(forward, (vec3) { -right[0], -right[1], -right[2] }, up);
    glm_normalize(up);

    glm_vec3_scale(right, right_speed, right);
    glm_vec3_scale(forward, forward_speed, forward);
    glm_vec3_scale(up, up_speed, up);

    glm_vec3_add(camera->pos, right, camera->pos);
    glm_vec3_add(camera->pos, forward, camera->pos);
    glm_vec3_add(camera->pos, up, camera->pos);
}