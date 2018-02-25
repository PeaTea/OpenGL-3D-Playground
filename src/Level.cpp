#include "Level.h"

#include <iostream>
#include <random>
#include <ctime>

#include "OutUtils.h"
#include "RenderGame.h"
#include "Settings.h"
#include "Maths.h"

/*
===============	Level notes	==============
levels[0] = Tutorial:
    Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

Level::Level(unsigned int lvl_id, const std::string& path, const glm::vec3& start_positions, float xz_scaling, float y_scaling)
    :   startPositions  {start_positions}
    ,   xz_scaling      {xz_scaling}
    ,   y_scaling       {y_scaling}
    ,   m_id            {lvl_id}
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
    newTexSize = {Settings::tex_size() * xz_scaling,
                  Settings::tex_size() * y_scaling};
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

glm::vec3 Level::center() const
{
    return {((w - 1) * newTexSize.x) / 2, 0, ((h - 1) * newTexSize.x) / 2};
}

Vec2<float> Level::scaling() const
{
    return {xz_scaling, y_scaling};
}

const unsigned char* Level::get_data()
{
    return image.getPixelsPtr();
}

sf::Color Level::get_pixel(int x, int y) const
{
    x = maths::clamp(x, 0, w - 1);
    y = maths::clamp(y, 0, h - 1);
    return image.getPixel(x, y);
}

glm::vec3& Level::start()
{
    return startPositions;
}

Vec2<float> Level::scaled_tex_size() const
{
    return newTexSize;
}

void Level::init(const std::unordered_map<int, GLTexture>& textures, const std::vector<Level>& levels, const glm::vec3& cam_pos,
                 std::unordered_map<std::string, GLProgram>& programs)
{
    data.init(m_id, textures, levels, cam_pos, programs);
}
