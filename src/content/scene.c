#include "scene.h"

#include "planet/planet_meta.h"
#include "planet/planet.h"
#include "camera/camera.h"
#include "planet/planets.h"

typedef struct Scene {
    GLFWwindow* window;
    Camera camera;
} Scene;

static Scene scene;

void InitScene(GLFWwindow* window) {
    scene.window = window;
    scene.camera = CreateCamera(60.0f, window);

    InitPlanets(&scene.camera);
}

void UpdateScene(float delta) {
    UpdateCamera(&scene.camera, delta);
    UpdatePlanets(delta);
}

void ResizeScene(int width, int height) {
    ResizeCamera(&scene.camera, width, height);
}

void CursorMovedScene([[maybe_unused]] float x_pos, [[maybe_unused]] float y_pos, float x_delta, float y_delta) {
    RotateCamera(&scene.camera, x_delta, y_delta);
}

void DisposeScene() {
    DisposePlanets();
}
