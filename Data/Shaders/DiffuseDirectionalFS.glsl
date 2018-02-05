#version 330 core

in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 color;

uniform vec3 light_dir;
uniform vec3 light_color;
uniform vec4 spritecolor;
uniform sampler2D image;

void main()
{
    float darkest = 0.2f;
    vec4 ambient_result = darkest * vec4(light_color, 1.0);

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(frag_pos - light_pos);

    float difference = max(dot(norm, light_dir), 0.0);
    vec4 diffuse_result = difference * vec4(light_color, 1.0);

    vec4 total_result = (ambient_result + diffuse_result) * spritecolor;
    total_result.a = 1.0;
    color = total_result * texture(image, tex_coords);
}