#version 330 core

in vec3 Pos;
in vec3 Normal;
in vec2 UV;

out vec4 FragColor;

uniform vec3 uViewPos;
uniform sampler2D uLitTexture;
uniform sampler2D uDarkTexture;

void main() {
    vec3 lightDir = vec3(1.0, 0.0, 0.0);

    vec3 normal = normalize(Normal);
    float diffuse = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(uViewPos - Pos);
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);

//    float intensity = diffuse * 0.8 + specular * 0.2;
    float intensity = diffuse;
    vec4 albedo = mix(texture(uDarkTexture, UV), texture(uLitTexture, UV), intensity);
    FragColor = vec4(albedo.rgb * (specular * 0.2 + 0.8), 1.0);
}