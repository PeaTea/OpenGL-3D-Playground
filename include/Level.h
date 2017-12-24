#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp>
#include "GLTexture.h"

class Level
{
public:
    Level(const std::string& path, const glm::vec3& start_positions, int wall_scaling);
    ~Level();

    int width() const;
    int height() const;
    int wall_scaling() const;
    const unsigned char* get_data();
    sf::Color get_pixel(unsigned int x, unsigned int y) const;
    glm::vec3& start();

private:
    int w;
    int h;
    int wallScaling;
    sf::Image image;
    glm::vec3 startPositions;
};

#endif