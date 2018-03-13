!shadertype::vertex
#version 330 core

layout(location = 0) in vec3 _pos;
layout(location = 1) in vec3 _normal;

out VS_OUT
{
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp;
uniform vec3 view_pos;

void main(void)
{
    gl_Position = mvp * vec4(_pos, 1);
    mat3 normal_matrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = vec3(projection * vec4(normal_matrix * _normal, 0.0));
}

!shadertype::fragment
#version 330 core

out vec4 color;

void main(void)
{
    color = vec4(0, 1, 0, 1);
}

!shadertype::geometry
#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT
{
    vec3 normal;
} gs_in[];

const float STRENGTH = 0.4;

void generate_line(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * STRENGTH;
    EmitVertex();
    EndPrimitive();
}

void main(void)
{
    generate_line(0);
    generate_line(1);
    generate_line(2);
}


