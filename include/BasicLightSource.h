#pragma once

#include <glm/glm.hpp>
#include <SFML/System/Clock.hpp>

#include "Level.h"

class Skybox;

class BasicLightSource
{
public:
    BasicLightSource(GLTexture texture, const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, 
                     float radius, float distance, Level lvl);
    BasicLightSource(const glm::vec3& pos, float radius, float distance, const glm::vec4& color, Level lvl);

    glm::vec3 position() const;
    glm::vec4 color() const;
    float radius() const;

    glm::vec3 rotate_around_center(const float& speed = 0.1f);
    glm::vec3 rotate_with_skybox(const float& speed = 0.1f);

    void render();

private:
    glm::vec4 m_color;

    glm::vec3 m_pos;
    glm::vec3 m_direction;
    glm::vec3 m_level_center;
    glm::vec3 m_first_pos;

    glm::vec2 m_size;

    GLTexture m_texture;

    sf::Clock clock;

    bool m_has_texture;
    float m_radius;
    float m_distance;
};