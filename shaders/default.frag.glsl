#version 330 core

in vec2 uvs;

uniform vec4 color;
uniform sampler2D textureID;

out vec4 fragColor;

void main() {
    fragColor = texture(textureID, uvs) * color;
}
