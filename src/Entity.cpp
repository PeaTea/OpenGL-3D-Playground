#include "Entity.h"

Entity::Entity(unsigned int tex_id, const glm::vec3& pos, const Vec2<float>& size,
               GLfloat rotation, const glm::vec3& rotation_vec,
               const glm::vec4& color)
    :   m_texture_id    {tex_id}
    ,   m_position      {pos}
    ,   m_size          {size}
    ,   m_rotation      {rotation}
    ,   m_rotation_vec  {rotation_vec}
    ,   m_color         {color}
    ,   m_is_rotated    {false}
    ,   m_cam_pos       {}
{
}

Entity::Entity(unsigned int tex_id, const glm::vec3& pos, const glm::vec3& cam_pos,
               const Vec2<float>& size, const glm::vec4& color)
    :   m_texture_id    {tex_id}
    ,   m_position      {pos}
    ,   m_cam_pos       {cam_pos}
    ,   m_size          {size}
    ,   m_color         {color}
    ,   m_is_rotated    {true}
    ,   m_rotation      {}
    ,   m_rotation_vec  {}
{
}


void Entity::set_cam_pos(const glm::vec3& cam_pos)
{
    if(m_is_rotated)
    {
        m_cam_pos = cam_pos;
    }
}


void Entity::render(std::unordered_map<std::string, GLProgram>& programs, const int& cf_height)
{
    BasicRenderer::set_program(m_is_rotated ? programs["point"] : programs["normal"]);
    (m_is_rotated) ? BasicRenderer::draw_sprite_facing_cam(m_texture_id, {m_position.x, m_position.y - cf_height, m_position.z},
                                                      m_cam_pos, m_size, m_color)
                   : BasicRenderer::draw_sprite(m_texture_id, {m_position.x, m_position.y - cf_height, m_position.z},
                                           m_size, m_rotation, m_rotation_vec, m_color);
}

glm::vec3 Entity::get_position() const
{
    return m_position;
}


glm::vec4 Entity::get_color() const
{
    return m_color;
}

