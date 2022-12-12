#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform float visibility;

void main()
{
    FragColor = texture(texture0, TexCoord);
}