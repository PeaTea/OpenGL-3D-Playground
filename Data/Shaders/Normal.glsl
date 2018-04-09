!shadertype::vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoords;

out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{
	gl_Position = projection * view * model * vec4(position.x, -position.y, position.z, 1.0);
	tex_coords = texcoords;
}


!shadertype::fragment
#version 330 core

in vec2 tex_coords;

out vec4 color;

uniform vec4 spritecolor;
uniform sampler2D image;

void main(void)
{
    vec4 texel = texture(image, tex_coords);
	if(texel.a < 0.4)
		discard;
	color = spritecolor;
}