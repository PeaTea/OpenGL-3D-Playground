#include "Skybox.h"
#include "GLShader.h"
#include "File.h"
#include "OutUtils.h"

#include <glm/gtc/matrix_transform.hpp>

const uint ROTATION_DIV = 5000000;

glm::vec3 Skybox::s_rotation_vec = {0, 0, 0};

Skybox::Skybox(const GLTextureCube& cube_map, const glm::vec3& position, const float& size,
               conststrref vspath, conststrref fspath)
    :   m_cube_map  {cube_map}
    ,   m_position  {position}
    ,   m_size      {size}
{
    generate_vao();
    generate_program(vspath, fspath);
}

Skybox::Skybox()
{
}

void Skybox::init(const GLTextureCube& cube_map, const glm::vec3& position, const int& size,
                  conststrref vspath, conststrref fspath)
{
    m_cube_map = cube_map;
    m_position = position;
    m_size = size;

    generate_vao();
    generate_program(vspath, fspath);
}

void Skybox::render(glm::mat4 view_mat, const glm::mat4& proj_mat, float dt, float rotation_angle, const glm::vec3& rotation_vec)
{
    Skybox::s_rotation_vec = rotation_vec;

    view_mat[3][0] = 0;
    view_mat[3][1] = 0;
    view_mat[3][2] = 0;

    float rotation = rotation_angle * (dt / ROTATION_DIV);
    model = glm::rotate(model, glm::degrees(rotation), rotation_vec);

    m_program.use();
    m_program.set_mat4("view", view_mat);
    m_program.set_mat4("proj", proj_mat);
    m_program.set_mat4("model", model);

    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
   
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cube_map.id());
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Skybox::generate_program(conststrref vspath, conststrref fspath)
{
    GLShader vertex({vspath}, Shadertype::VERTEX);
    GLShader fragment({fspath}, Shadertype::FRAGMENT);

    m_program.create();
    m_program.attach_shader(vertex);
    m_program.attach_shader(fragment);
    m_program.link();
}


void Skybox::generate_vao()
{
    GLfloat skybox_vertices[] =
    {
        -m_size, m_size, -m_size,
        -m_size, -m_size, -m_size,
        m_size, -m_size, -m_size,
        m_size, -m_size, -m_size,
        m_size, m_size, -m_size,
        -m_size, m_size, -m_size,

        -m_size, -m_size, m_size,
        -m_size, -m_size, -m_size,
        -m_size, m_size, -m_size,
        -m_size, m_size, -m_size,
        -m_size, m_size, m_size,
        -m_size, -m_size, m_size,

        m_size, -m_size, -m_size,
        m_size, -m_size, m_size,
        m_size, m_size, m_size,
        m_size, m_size, m_size,
        m_size, m_size, -m_size,
        m_size, -m_size, -m_size,

        -m_size, -m_size, m_size,
        -m_size, m_size, m_size,
        m_size, m_size, m_size,
        m_size, m_size, m_size,
        m_size, -m_size, m_size,
        -m_size, -m_size, m_size,

        -m_size, m_size, -m_size,
        m_size, m_size, -m_size,
        m_size, m_size, m_size,
        m_size, m_size, m_size,
        -m_size, m_size, m_size,
        -m_size, m_size, -m_size,

        -m_size, -m_size, -m_size,
        -m_size, -m_size, m_size,
        m_size, -m_size, -m_size,
        m_size, -m_size, -m_size,
        -m_size, -m_size, m_size,
        m_size, -m_size, m_size
    };

    GLuint vbo;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), skybox_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, (GLvoid*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}