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
    const float pi = 3.14159265;
    const float minApparentArea = 5.0;

    vec3 vertexPos = (uModel * vec4(aPos, 1.0)).xyz;
    vec3 center = (uModel * vec4(0.0, 0.0, 0.0, 1.0)).xyz;

    vec3 toCenter = center - uViewPos;
    float dst = length(toCenter);

    float radius = length(uModel[0].xyz);
    float maxDst = radius * uFrameSize.y * 0.5 * sqrt(pi / minApparentArea);
    float clampedDst = min(dst, maxDst);

    vec3 direction = dst > 0.0001 ? toCenter / dst : vec3(0.0, 0.0, 1.0);
    vec3 adjustedCenter = uViewPos + direction * clampedDst;
    vec3 adjustedPos = adjustedCenter + (vertexPos - center);

    gl_Position = uProj * uView * vec4(adjustedPos, 1.0);

    Pos = adjustedPos;
    Normal = normalize(transpose(inverse(mat3(uModel))) * aNormal);
    UV = aUV;

    float projectedRadius = radius * uFrameSize.y / (2.0 * max(dst, 0.0001));
    float projectedArea = pi * projectedRadius * projectedRadius;

    Alpha = min(projectedArea / minApparentArea, 1.0);
}