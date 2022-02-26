#version 460 core

out vec4 FragColor;

in vec2 aCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float visibility;

void main()
{
    FragColor = mix(texture(texture0, aCoord), texture(texture1, vec2(aCoord.x * 2, aCoord.y * 2)), visibility);
}