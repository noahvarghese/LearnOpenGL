#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float visibility;

void main()
{
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(TexCoord.x * 2, TexCoord.y * 2)), visibility);
}