#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normals;
layout (location = 2) in vec2 a_uvs;

out vec2 uvs;
out vec3 normals;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragPos = vec3(model * vec4(a_pos, 1.0));
    normals = mat3(transpose(inverse(model))) * a_normals;
    uvs = a_uvs;
    gl_Position = projection * view * vec4(fragPos, 1.0);
}
