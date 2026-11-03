#include "../planet.h"

Planet CreatePlanet() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), planet->vertices, GL_STATIC_DRAW);
}

void RenderPlanet(Planet* planet) {

}
