#version 330 core

in vec3 colorFrag;
out vec4 color;

void main()
{
    color = vec4(colorFrag, 1.0f);
}