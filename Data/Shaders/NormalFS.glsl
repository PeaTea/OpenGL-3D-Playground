#version 330 core

in vec2 tex_coords;

out vec4 color;

uniform vec4 spritecolor;
uniform sampler2D image;
uniform float time;

void main(void)
{
    vec4 texel = spritecolor * texture(image, tex_coords);
	if(texel.a < 0.4)
		discard;
	color = texel;
}