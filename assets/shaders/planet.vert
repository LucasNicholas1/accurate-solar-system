#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec3 Pos;
out vec3 Normal;
out vec2 UV;
out float Alpha;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;
uniform vec3 uViewPos;
uniform vec2 uFrameSize;

void main() {
    // World position of vertex
    vec3 vertexPos = (uModel * vec4(aPos, 1.0)).xyz;

    // Distance from camera to planet center
    vec3 center = (uModel * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    float dst = length(center - uViewPos);

    // Approximate projected planet area in pixels
    float radius = max(length(vec3(
                              uModel[0][0],
                              uModel[1][0],
                              uModel[2][0]
                              )), 0.0001);

    float projectedRadius = radius * uFrameSize.y / (2.0 * dst);

    float projectedArea = 3.14159265 * projectedRadius * projectedRadius;

    // Minimum projected area: 1 pixel squared
    float scale = sqrt(max(10.0, projectedArea) / max(projectedArea, 0.000001));
//    float alpha = min(3.14159265 / (dst * dst), 1.0);
    float alpha = 1.0;

    // Scale around the planet center, not the world origin
    vec3 adjustedPos = center + (vertexPos - center) * scale;

    gl_Position = uProj * uView * vec4(adjustedPos, 1.0);

    Pos = adjustedPos;
    Normal = normalize(transpose(inverse(mat3(uModel))) * aNormal);
    UV = aUV;
    Alpha = alpha;
}