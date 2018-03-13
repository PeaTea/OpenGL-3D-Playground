!shadertype::vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texcoords;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	tex_coords = texcoords;
}


!shadertype::fragment
#version 330 core

in vec2 tex_coords;

out vec4 color;

uniform vec4 spritecolor;
uniform sampler2D image;
uniform float time;

void main(void)
{
    vec4 dark_spritecolor = spritecolor * vec4(0.3, 0.3, 0.3, 1.0);

    vec4 texel = dark_spritecolor * texture(image, tex_coords);
	if(texel.a < 0.4)
		discard;
	color = texel;
}