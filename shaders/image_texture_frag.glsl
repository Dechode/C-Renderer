#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D u_Texture;

void main()
{
//    fragColor = texture(u_Texture, texCoord) + vec4(color, 0.0);
    fragColor = texture(u_Texture, texCoord); //* vec4(color, 0.0);
}
