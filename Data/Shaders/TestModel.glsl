!shadertype::vertex
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 mvp;

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

in vec3 _normal;
in vec3 _pos;

out vec4 color;

uniform vec3 view_pos;
uniform mat4 model;

vec3 light_dir = normalize(-vec3(-1, 1, -1));
float darkest = 0.4f;
float specular_str = 0.5f;

void main(void)
{
    vec3 norm = normalize(_normal);

    vec3 ambient = vec3(darkest, darkest, darkest);

    float diff = max(dot(norm, light_dir), 0);
    vec3 diffuse = vec3(diff, diff, diff) * vec3(1, 1, 0.5);

    vec3 frag_pos = vec3(model * vec4(_pos, 1));
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);

    float spec = pow(max(dot(view_dir, reflect_dir), 0), 64);
    vec3 specular = specular_str * spec * vec3(1, 1, 0.5);

    color = vec4(ambient + diffuse + specular, 1.0);
}