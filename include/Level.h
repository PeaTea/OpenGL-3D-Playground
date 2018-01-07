#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp>
#include <map>

#include "GLTexture.h"
#include "Vec2.h"
#include "LevelData.h"

class Level
{
public:
    Level(unsigned int lvl_id, const std::string& path, const glm::vec3& start_positions, float xz_scaling, float y_scaling);
    ~Level();

    unsigned int width() const;
    unsigned int height() const;

    const unsigned char* get_data();
    sf::Color get_pixel(unsigned int x, unsigned int y) const;

    Vec2 scaling() const;
    glm::vec3& start();
    Vec2 scaled_tex_size() const;

    void init(const std::vector<GLTexture>& textures, const std::vector<Level>& levels, const glm::vec3& cam_pos,
              std::map<std::string, GLProgram>& programs);

    LevelData data;

private:
    float xz_scaling, y_scaling;
    unsigned int w, h, m_id;
    sf::Image image;
    glm::vec3 startPositions;
    Vec2 newTexSize;
};

#endif