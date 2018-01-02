#include "Level.h"

#include <iostream>
#include <random>
#include <ctime>

#include "Logging.h"
#include "RenderGame.h"

using RG_GB::TEX_SIZE;

/*
===============	Level notes	==============
levels[0] = Tutorial:
    Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

Level::Level(const std::string& path, const glm::vec3& start_positions, int xz_scaling, int y_scaling)
    :   startPositions  {start_positions}
    ,   xz_scaling      {xz_scaling}
    ,   y_scaling       {y_scaling}
{
    if(!image.loadFromFile(path))
    {
        logging::log("Could not load file: " + path, lstream::error);
    }
    if(xz_scaling == 0 || y_scaling == 0)
    {
        logging::log("scaling = 0", lstream::error);
    }

    w = image.getSize().x;
    h = image.getSize().y;
    newTexSize = {TEX_SIZE.x * xz_scaling, TEX_SIZE.y * y_scaling};
}

Level::~Level()
{
}


int Level::width() const
{
    return w;
}

int Level::height() const
{
    return h;
}

glm::vec2 Level::scaling() const
{
    return glm::vec2(xz_scaling, y_scaling);
}

const unsigned char* Level::get_data()
{
    return image.getPixelsPtr();
}

sf::Color Level::get_pixel(unsigned int x, unsigned int y) const
{
    return image.getPixel(x, y);
}

glm::vec3& Level::start()
{
    return startPositions;
}

Vec2 Level::scaled_tex_size() const
{
    return newTexSize;
}
