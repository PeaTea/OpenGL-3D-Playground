#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal_vec;
layout(location = 2) in vec2 texture_coords;

out vec3 normal;
out vec3 frag_pos;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    normal = normal_vec;
    frag_pos = vec3(model * vec4(position, 1.0));
    tex_coords = texture_coords;
}