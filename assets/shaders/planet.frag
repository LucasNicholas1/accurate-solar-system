#version 330 core

in vec3 Pos;
in vec3 Normal;
in vec2 UV;
in float Alpha;

out vec4 FragColor;

uniform vec3 uViewPos;
uniform sampler2D uLitTexture;
uniform sampler2D uDarkTexture;
uniform bool uBinaryTexture;

void main() {
    vec3 lightDir = normalize(-Pos);

    vec3 normal = normalize(Normal);
    float dst = length(Pos);
    float diffuse = max(dot(normal, lightDir), 0.0) / (dst * dst) * 1000.0;

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(uViewPos - Pos);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);

//    float intensity = diffuse * 0.8 + specular * 0.2;
    float intensity = diffuse;
    vec4 lit = texture(uLitTexture, UV);
    vec4 dark = texture(uDarkTexture, UV);

//    intensity = 1.0;

    vec4 albedo;
    if (uBinaryTexture) {
        albedo = dark + lit * intensity;
    } else {
        albedo = lit * intensity;
    }

    FragColor = vec4(albedo.rgb * Alpha, 1.0);
}