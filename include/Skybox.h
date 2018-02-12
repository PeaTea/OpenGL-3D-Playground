#pragma once

#include "Types.h"
#include "GLTexture.h"
#include "GLProgram.h"

#include <glm/glm.hpp>

class Skybox
{
public:
    Skybox(const GLTextureCube& cube_map, const glm::vec3& position, const int& size,
           conststrref vspath, conststrref fspath);

    Skybox();

    void init(const GLTextureCube& cube_map, const glm::vec3& position, const int& size,
              conststrref vspath, conststrref fspath);

    void render(glm::mat4 view_mat, const glm::mat4& proj_mat, float dt, float rotation_angle = 1.0f, const glm::vec3& rotation_vec = {1, 1, 1});

private:
    void generate_vao();
    void generate_program(conststrref vspath, conststrref fspath);

    GLuint m_vao;
    GLTextureCube m_cube_map;
    GLProgram m_program;

    glm::vec3 m_position;
    int m_size;

    glm::mat4 model;
};

