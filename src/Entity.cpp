#include "Entity.h"

Entity::Entity(unsigned int tex_id, const glm::vec3& pos, const Vec2& size,
               GLfloat rotation, const glm::vec3& rotation_vec,
               const glm::vec4& color)
    :   m_texture_id    {tex_id}
    ,   m_position      {pos}
    ,   m_size          {size}
    ,   m_rotation      {rotation}
    ,   m_rotation_vec  {rotation_vec}
    ,   m_color         {color}
    ,   m_is_rotated    {false}
{
}

Entity::Entity(unsigned int tex_id, const glm::vec3& pos, const glm::vec3& cam_pos,
               const Vec2& size, const glm::vec4& color)
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
    } else return;
}


void Entity::render(std::map<std::string, GLProgram>& programs)
{
    if(m_is_rotated)
    {
        Renderer::set_program(programs["darken"]);
    }
    else
    {
        Renderer::set_program(programs["normal"]);
    }
    (m_is_rotated) ? Renderer::draw_sprite_facing_cam(m_texture_id, m_position, m_cam_pos, m_size, m_color)
                   : Renderer::draw_sprite(m_texture_id, m_position, m_size, m_rotation, m_rotation_vec, m_color);
}

