#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp>
#include "GLTexture.h"
#include "Vec2.h"

class Level
{
public:
    Level(const std::string& path, const glm::vec3& start_positions, int xz_scaling, int y_scaling);
    ~Level();

    int width() const;
    int height() const;
    glm::vec2 scaling() const;
    const unsigned char* get_data();
    sf::Color get_pixel(unsigned int x, unsigned int y) const;
    glm::vec3& start();
    Vec2 scaled_tex_size() const;

private:
    int xz_scaling, y_scaling, w, h;
    sf::Image image;
    glm::vec3 startPositions;
    Vec2 newTexSize;
};

#endif