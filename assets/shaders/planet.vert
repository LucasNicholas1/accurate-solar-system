#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 Pos;
out vec3 Normal;
out vec2 UV;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
    Pos = (uModel * vec4(aPos, 1.0)).xyz;
    Normal = normalize(transpose(inverse(mat3(uModel))) * aNormal);
    UV = aUV;
}