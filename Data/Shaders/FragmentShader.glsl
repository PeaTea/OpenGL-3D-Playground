#version 330 core

in vec2 tex_coords;

out vec4 color;

uniform vec4 spritecolor;
uniform sampler2D image;

void main(void)
{
	color = spritecolor * texture(image, tex_coords);
}