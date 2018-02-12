#version 330 core

in vec3 tex_coords;

out vec4 color;

uniform samplerCube cube_map;

void main()
{
    color = texture(cube_map, tex_coords);
}