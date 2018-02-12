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

    int width() const;
    int height() const;
    glm::vec3 center() const;

    const unsigned char* get_data();
    sf::Color get_pixel(unsigned int x, unsigned int y) const;

    Vec2<float> scaling() const;
    glm::vec3& start();
    Vec2<float> scaled_tex_size() const;

    void init(const std::vector<GLTexture>& textures, const std::vector<Level>& levels, const glm::vec3& cam_pos,
              std::map<std::string, GLProgram>& programs);

    LevelData data;

private:
    float xz_scaling, y_scaling;
    int w, h;
    unsigned int m_id;
    sf::Image image;
    glm::vec3 startPositions;
    Vec2<float> newTexSize;
};

#endif