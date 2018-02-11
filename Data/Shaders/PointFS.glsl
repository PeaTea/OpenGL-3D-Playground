#version 330 core

#define MAX_LIGHTS 16

struct PointLight
{
    vec3 position;
    vec4 color;
    
    float radius;
};


in vec3 normal;
in vec3 frag_pos;
in vec2 tex_coords;

out vec4 color;

uniform int num_lights;
uniform PointLight point_lights[MAX_LIGHTS];
uniform vec4 spritecolor;
uniform sampler2D image;


vec3 calculate_point_light(PointLight light, vec3 pos_difference, float darkest)
{
    // Ambient
    vec4 ambient_result = darkest * vec4(1, 1, 1, 1);

    float distance = length(pos_difference);
    float attenuation = clamp(1 - (distance * distance) / (light.radius * light.radius), 0, 1);
    float brightness = clamp((dot(normal, pos_difference) / length(pos_difference) * length(normalize(normal))) * attenuation, 0, 1);

    vec4 diffuse_result = brightness * light.color;

    return vec3((ambient_result + diffuse_result) * spritecolor);
}

void main()
{
    float darkest = 0.001;

    vec3 result = vec3(darkest, darkest, darkest);

    for(int i = num_lights; i > 0; i--)
    {
        if(i > MAX_LIGHTS)
            discard;
        result += calculate_point_light(point_lights[i], point_lights[i].position - frag_pos, darkest);
    }

    color = vec4(result, 1.0) * texture(image, tex_coords);
}