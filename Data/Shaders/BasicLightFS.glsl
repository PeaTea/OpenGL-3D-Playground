#version 330 core

out vec4 color;

uniform vec3 obj_color;
uniform vec3 light_color;

void main()
{
	color = vec4(obj_color * light_color, 1.0);
}