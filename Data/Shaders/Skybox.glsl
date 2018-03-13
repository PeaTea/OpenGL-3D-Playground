!shadertype::vertex
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


!shadertype::fragment
#version 330 core

in vec3 tex_coords;

out vec4 color;

uniform samplerCube cube_map;

void main()
{
    color = texture(cube_map, tex_coords);
}