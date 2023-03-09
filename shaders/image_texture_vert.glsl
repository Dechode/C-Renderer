#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 color;
out vec2 texCoord;

void main()
{
//    gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
    gl_Position = vec4(a_Pos, 1.0);
    color = a_Color;
    texCoord = a_TexCoord;
}
