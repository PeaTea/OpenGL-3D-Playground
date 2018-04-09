#include "BasicLightSource.h"
#include "Skybox.h"


BasicLightSource::BasicLightSource(GLTexture texture, const glm::vec3& pos, const glm::vec2& size,
                                   const glm::vec4& color, float radius, float distance, Image lvl)
    :   m_pos           {pos}
    ,   m_size          {size}
    ,   m_level_center  {lvl.center()}
    ,   m_direction     {m_level_center - m_pos}
    ,   m_texture       {texture}
    ,   m_color         {color}
    ,   m_first_pos     {pos}
    ,   m_has_texture   {true}
    ,   m_radius        {radius}
    ,   m_distance      {distance}
{
}


BasicLightSource::BasicLightSource(const glm::vec3& pos, float radius, float distance,
                                   const glm::vec4& color, Image lvl)
    :   m_pos           {pos}
    ,   m_size          {radius, radius}
    ,   m_level_center  {lvl.center()}
    ,   m_direction     {m_level_center - m_pos}
    ,   m_texture       {"NONE"}
    ,   m_color         {color}
    ,   m_first_pos     {pos}
    ,   m_has_texture   {false}
    ,   m_radius        {radius}
    ,   m_distance      {distance}
{
}


glm::vec3 BasicLightSource::position() const
{
    return m_pos;
}

glm::vec4 BasicLightSource::color() const
{
    return m_color;
}

float BasicLightSource::radius() const
{
    return m_radius;
}

glm::vec3 BasicLightSource::rotate_around_center(const float& speed)
{
    m_pos.x = sin(clock.getElapsedTime().asSeconds() * speed) * m_distance + m_first_pos.x;
    m_pos.z = cos(clock.getElapsedTime().asSeconds() * speed) * m_distance + m_first_pos.z;

    m_direction = (m_level_center - m_pos);
    
    return m_direction;
}

glm::vec3 BasicLightSource::rotate_with_skybox(const float& speed)
{
    glm::vec3 rv = Skybox::s_rotation_vec;

    m_pos.x = (cos(clock.getElapsedTime().asSeconds() * speed * 100) * m_distance + m_first_pos.x) * rv.x;
    m_pos.y = (sin(clock.getElapsedTime().asSeconds() * speed) * m_distance + m_first_pos.y) * rv.y;
    m_pos.z = (sin(clock.getElapsedTime().asSeconds() * speed) * m_distance + m_first_pos.z) * rv.z;

    m_direction = (m_level_center - m_pos);

    return m_direction;
}

void BasicLightSource::render()
{
    if(m_has_texture)
        BasicRenderer::draw_sprite_facing_cam(m_texture.id(), m_pos, m_level_center, {m_size.x, m_size.y}, m_color);
}