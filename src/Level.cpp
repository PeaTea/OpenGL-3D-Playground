#include "Level.h"
#include <iostream>
#include "RenderGame.h"
#include <random>
#include <ctime>

using RG_GB::TEX_SIZE;

/*
===============	Level notes	==============
levels[0] = Tutorial:
    Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

Level::Level(const std::string& path, const glm::vec3& start_positions, int wall_scaling)
    :   startPositions  {start_positions}
    ,   wallScaling     {wall_scaling}
{
    if(!image.loadFromFile(path))
    {
        std::cout << "Could not load file: " << path << std::endl;
    }

    w = image.getSize().x;
    h = image.getSize().y;
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

int Level::wall_scaling() const
{
    return wallScaling;
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
