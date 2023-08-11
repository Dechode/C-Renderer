#version 330 core 

out vec4 fragColor;

uniform vec3 color;
uniform vec3 lightColor;

void main() {
    float ambientStr = 0.15;
    vec3 ambient = ambientStr * lightColor;
    vec3 result = color * lightColor;
    fragColor = vec4(result, 1.0);
}
