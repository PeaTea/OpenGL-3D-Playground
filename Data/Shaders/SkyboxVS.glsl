#version 330 core

layout(location = 0) in vec3 position;

out vec3 tex_coords;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(position, 1.0);
    tex_coords = position;
}