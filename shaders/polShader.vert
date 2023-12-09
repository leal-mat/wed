#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color_a;

uniform mat4 m_proj;
uniform mat4 m_view;
out vec3 colorFrag;


void main()
{
    gl_Position  = m_proj*m_view*vec4(position, 1.0);
    colorFrag = color_a;

}
