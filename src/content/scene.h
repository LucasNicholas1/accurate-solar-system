#ifndef ACCURATE_SOLAR_SYSTEM_SCENE_H
#define ACCURATE_SOLAR_SYSTEM_SCENE_H

typedef struct GLFWwindow GLFWwindow;

void InitScene(GLFWwindow* window);
void UpdateScene(float delta);
void ResizeScene(int width, int height);
void CursorMovedScene(float x_pos, float y_pos, float x_delta, float y_delta);
void DisposeScene();

#endif //ACCURATE_SOLAR_SYSTEM_SCENE_H
