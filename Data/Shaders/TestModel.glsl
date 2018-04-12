!shadertype::vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;
uniform mat4 model;

out vec3 _normal;
out vec3 _pos;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    _normal = normal;
    _pos = position;
}


!shadertype::fragment
#version 330 core
#define POINT_LIGHTING

in vec3 _normal;
in vec3 _pos;
in vec3 _frag_pos;

out vec4 color;

uniform vec3 view_pos;
uniform mat4 model;

#ifndef POINT_LIGHTING

vec3 light_dir = normalize(-vec3(0, -1, 0));
float darkest = 0.4f;
float specular_str = 2.0f;

void main(void)
{
    vec3 norm = normalize(_normal);

    vec3 ambient = vec3(darkest, darkest, darkest);

    float diff = max(dot(norm, light_dir), 0);
    vec3 diffuse = vec3(diff, diff, diff) * vec3(1, 1, 0.5);

    vec3 frag_pos = vec3(model * vec4(_pos, 1));
    vec3 view_dir = normalize(view_pos - _pos);
    vec3 reflect_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0), 64);
    vec3 specular = specular_str * spec * vec3(1, 1, 0.5);

    color = vec4(ambient + diffuse + specular, 1.0);
}
#else

float darkest = 0.01;
vec3 light_position = vec3(2, 10, 2);
float light_radius = 2000000;
float specular_str = 1.0f;

vec3 calculate_point_light(vec3 pos_difference, vec3 frag_pos)
{
    vec3 norm = normalize(_normal);
    vec4 ambient_result = darkest * vec4(1, 1, 1, 1);

    float distance = length(pos_difference);
    float attenuation = clamp(1 - (distance * distance) / (light_radius * light_radius), 0, 1);
    float brightness = clamp((dot(_normal, pos_difference) / length(pos_difference) * length(normalize(_normal))) * attenuation, 0, 1);

    vec4 diffuse_result = brightness * vec4(0.5, 0.5, 0.5, 1);

    vec3 view_dir = normalize(view_pos - _pos);
    vec3 reflect_dir = reflect(normalize(-pos_difference), norm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0), 64);
    vec4 specular_result = vec4(specular_str * spec * vec3(1, 1, 1), 1);

    return vec3((ambient_result + diffuse_result + specular_result));
}

void main(void)
{
    vec3 result = vec3(darkest, darkest, darkest);
    vec3 frag_pos = vec3(model * vec4(_pos, 1));

    result += calculate_point_light(light_position - frag_pos, frag_pos);

    color = vec4(result, 1.0);
}

#endif