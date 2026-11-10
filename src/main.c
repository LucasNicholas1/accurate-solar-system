#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "content/scene.h"

static void error(int error, const char* description);
static void framebufferSize(GLFWwindow* window, int width, int height);
static void cursorPos(GLFWwindow* window, double x_pos, double y_pos);

int main() {
    glfwSetErrorCallback(error);

    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Earth", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebufferSize);
    glfwSetCursorPosCallback(window, cursorPos);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize glad\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);

    InitScene(window);

    double prev_time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        double curr_time = glfwGetTime();
        float delta = (float) (curr_time - prev_time);
        prev_time = curr_time;

        constexpr float max_delta = 0.25f;
        if (delta < max_delta) {
            delta = max_delta;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        UpdateScene(delta);

        glfwSwapBuffers(window);
    }

    DisposeScene();
    glfwTerminate();

    return EXIT_SUCCESS;
}

void error(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void framebufferSize([[maybe_unused]] GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    ResizeScene(width, height);
}

void cursorPos([[maybe_unused]] GLFWwindow* window, double x_pos, double y_pos) {
    static double x_prev;
    static double y_prev;
    static bool first_move = true;

    if (first_move) {
        x_prev = x_pos;
        y_prev = y_pos;
        first_move = false;
        return;
    }

    float x_delta = (float) (x_pos - x_prev);
    float y_delta = (float) (y_pos - y_prev);

    x_prev = x_pos;
    y_prev = y_pos;

    CursorMovedScene((float) x_pos, (float) y_pos, x_delta, y_delta);
}