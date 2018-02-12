#include "BasicLightSource.h"


BasicLightSource::BasicLightSource(GLTexture texture, const glm::vec3& pos, const glm::vec2& size,
                                   const glm::vec4& color, float radius, Level lvl)
    :   m_pos           {pos}
    ,   m_size          {size}
    ,   m_level_center  {lvl.center()}
    ,   m_direction     {m_level_center - m_pos}
    ,   m_texture       {texture}
    ,   m_color         {color}
    ,   m_first_pos     {pos}
    ,   m_has_texture   {true}
    ,   m_radius        {radius}
{
}


BasicLightSource::BasicLightSource(const glm::vec3& pos, float radius, const glm::vec4& color,
                                   Level lvl)
    :   m_pos           {pos}
    ,   m_size          {radius, radius}
    ,   m_level_center  {lvl.center()}
    ,   m_direction     {m_level_center - m_pos}
    ,   m_texture       {"NONE"}
    ,   m_color         {color}
    ,   m_first_pos     {pos}
    ,   m_has_texture   {false}
    ,   m_radius        {radius}
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

glm::vec3 BasicLightSource::rotate_around_center(float speed)
{
    float radius = glm::length(m_level_center) * 4;

    m_pos.x = sin(clock.getElapsedTime().asSeconds() * speed) * radius + m_first_pos.x;
    m_pos.z = cos(clock.getElapsedTime().asSeconds() * speed) * radius + m_first_pos.z;

    m_direction = (m_level_center - m_pos);
    
    return m_direction;
}

void BasicLightSource::render()
{
    if(m_has_texture)
        Renderer::draw_sprite_facing_cam(m_texture.id(), m_pos, m_level_center, {m_size.x, m_size.y}, m_color);
}