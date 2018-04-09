#include "Image.h"

#include <iostream>
#include <random>
#include <ctime>

#include "OutUtils.h"
#include "RenderGame.h"
#include "Settings.h"
#include "Maths.h"

/*
===============	Image notes	==============
levels[0] = Tutorial:
    Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

Image::Image(unsigned int lvl_id, const std::string& path, const glm::vec3& start_positions, float xz_scaling, float y_scaling)
    :   startPositions  {start_positions}
    ,   xz_scaling      {xz_scaling}
    ,   y_scaling       {y_scaling}
    ,   m_id            {lvl_id}
{
    if(!image.loadFromFile(path))
    {
        logging::log("Could not load file: " + path, lstream::exception);
    }
    if(xz_scaling == 0 || y_scaling == 0)
    {
        logging::log("scaling = 0", lstream::exception);
    }

    w = image.getSize().x;
    h = image.getSize().y;
    newTexSize = {Settings::tex_size() * xz_scaling,
                  Settings::tex_size() * y_scaling};
}

Image::~Image()
{
}


int Image::width() const
{
    return w;
}

int Image::height() const
{
    return h;
}

glm::vec3 Image::center() const
{
    return {((w - 1) * newTexSize.x) / 2, 0, ((h - 1) * newTexSize.x) / 2};
}

Vec2<float> Image::scaling() const
{
    return {xz_scaling, y_scaling};
}

const unsigned char* Image::get_data()
{
    return image.getPixelsPtr();
}

sf::Color Image::get_pixel(int x, int y) const
{
    x = maths::clamp(x, 0, w - 1);
    y = maths::clamp(y, 0, h - 1);
    return image.getPixel(x, y);
}

glm::vec3& Image::start()
{
    return startPositions;
}

Vec2<float> Image::scaled_tex_size() const
{
    return newTexSize;
}

void Image::init(const std::unordered_map<int, GLTexture>& textures, const std::vector<Image>& levels, const glm::vec3& cam_pos,
                 std::unordered_map<std::string, GLProgram>& programs)
{
    data.init(m_id, textures, levels, cam_pos, programs);
}
