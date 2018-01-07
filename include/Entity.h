#pragma once

#include "Vec2.h"
#include "GLTexture.h"
#include "Renderer.h"

#include <glm/glm.hpp>
#include <map>

class Entity
{
public:
    Entity(unsigned int tex_id, const glm::vec3& pos, const Vec2& size,
           GLfloat rotation = 0.0f, const glm::vec3& rotation_vec = {1, 0, 0},
           const glm::vec4& color = {1, 1, 1, 1});

    Entity(unsigned int tex_id, const glm::vec3& pos, const glm::vec3& cam_pos,
           const Vec2& size = {1, 1}, const glm::vec4& color = {1, 1, 1, 1});

    void render(std::map<std::string, GLProgram>& programs);

    void set_cam_pos(const glm::vec3& cam_pos);

private:
    Vec2 m_size;

    GLuint m_texture_id;
    GLfloat m_rotation;

    glm::vec3 m_position;
    glm::vec3 m_rotation_vec;
    glm::vec3 m_cam_pos;

    glm::vec4 m_color;

    bool m_is_rotated;
};
