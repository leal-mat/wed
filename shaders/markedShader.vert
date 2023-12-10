#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 m_proj;
uniform mat4 m_view;


void main()
{
    gl_Position  = m_proj*m_view*vec4(position, 1.0);
}