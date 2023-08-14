#version 330 core 

out vec4 fragColor;

uniform vec4 color;
uniform vec3 lightColor = vec3(1.0);

in vec2 uvs;

void main() {
    float ambientStr = 0.15;
    vec3 ambient = ambientStr * lightColor;
    vec3 result = color.rgb * lightColor;
    fragColor = vec4(result, 1.0);
}
