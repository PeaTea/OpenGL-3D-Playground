#include "ImageDrawer.h"
#include "RenderGame.h"
#include "Maths.h"

/*
===============	Level notes	==============
levels[0] = Tutorial:
Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

enum PixelID
{
    FLOOR,
    WALL_LEFT,
    WALL_RIGHT,
    WALL_UP,
    WALL_DOWN,
    CEILING
};

#include "../Data/Colors.data"

ImageDrawer::ImageDrawer()
{
    m_pixeldata[(int)PixelID::FLOOR].texture = MARBLE;
    m_pixeldata[(int)PixelID::FLOOR].color = LIGHT_GREY;

    m_pixeldata[(int)PixelID::CEILING].texture = MARBLE;
    m_pixeldata[(int)PixelID::CEILING].color = DARK_GREY;

    m_tex_size = Settings::tex_size();
    m_cf_height = (int)(m_tex_size * 0.5f);
}

void ImageDrawer::set_lvl(Level& lvl)
{
    xz_scaling = lvl.scaling().x;
    y_scaling= lvl.scaling().y;
    
    level_width = lvl.width();
    level_height = lvl.height();

    scaled_tex_size_xz = m_tex_size * xz_scaling;
    scaled_tex_size_y = m_tex_size * y_scaling;

    for(int i{}; i < level_width; i++)
    {
        for(int j{}; j < level_height; j++)
        {
            level_pixel_colors.emplace_back(lvl.get_pixel(i, j));
        }
    }
}

void ImageDrawer::render_2D(const std::unordered_map<int, GLTexture>& textures, const Level& lvl, GLProgram& program)
{
    BasicRenderer::set_program(program);
    for(int i = 0; i < lvl.width(); i++)
    {
        for(int j = 0; j < lvl.height(); j++)
        {
            sf::Color color = lvl.get_pixel(i, j);
            sf::Color wcolor_yl = (j == 0) ? sf::Color::Red : lvl.get_pixel(i, j - 1);                //Wall Color y left = up
            sf::Color wcolor_yr = (j + 1 == lvl.height()) ? sf::Color::Red : lvl.get_pixel(i, j + 1); //Wall Color y right = down
            sf::Color wcolor_xl = (i == 0) ? sf::Color::Red : lvl.get_pixel(i - 1, j);                //Wall Color x left = left
            sf::Color wcolor_xr = (i + 1 == lvl.width()) ? sf::Color::Red : lvl.get_pixel(i + 1, j);  //Wall Color x right = right

            sf::Color wcolors[4] = {wcolor_xl, wcolor_xr, wcolor_yl, wcolor_yr};

            float xz_scaling = lvl.scaling().x;
            float y_scaling = lvl.scaling().y;

            if(color != sf::Color::Black && color != sf::Color(255, 255, 255, 0))
            {
                for(int k = 0; k < 4; k++)
                {
                    if(wcolors[k] == sf::Color::Black)
                    {
                        m_pixeldata[k + 1].texture = METAL_CUBE;
                        m_pixeldata[k + 1].color = LIGHT_GREY;
                        skip[k] = false;
                    }
                    else if(wcolors[k] == sf::Color(192, 192, 192, 255) ||
                            wcolors[k] == sf::Color::Red ||
                            wcolors[k] == sf::Color(255, 255, 255, 0))
                    {
                        skip[k] = true;
                    }
                }
                
                //Floor
                BasicRenderer::draw_sprite(textures.at(m_pixeldata[FLOOR].texture).id(),
                                      {m_tex_size * i * xz_scaling, - (m_tex_size * 0.5), m_tex_size * j * xz_scaling},
                                      {m_tex_size * xz_scaling}, 90.0f, {1, 0, 0}, m_pixeldata[FLOOR].color);
            
                //Ceiling
                BasicRenderer::draw_sprite(textures.at(m_pixeldata[CEILING].texture).id(),
                                      {m_tex_size * i * xz_scaling, y_scaling  * m_tex_size - m_tex_size / 2, m_tex_size * j * xz_scaling},
                                      {m_tex_size * xz_scaling}, 270.0f, {1, 0, 0}, m_pixeldata[CEILING].color);
                
                //Walls 
                if(wcolor_xl != sf::Color::White)
                {
                    if(skip[WALL_LEFT - 1])
                    {
                        skip[WALL_LEFT - 1] = false;
                    }
                    else
                    {
                        BasicRenderer::draw_sprite(textures.at(m_pixeldata[WALL_UP].texture).id(),
                                              {m_tex_size * i * xz_scaling - m_tex_size / 2 - (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - m_tex_size / 2 : 0),
                                              y_scaling * m_tex_size / 2 - m_tex_size / 2, m_tex_size * j * xz_scaling + m_tex_size / 2 - m_tex_size / 2},
                                              {m_tex_size * xz_scaling, m_tex_size * y_scaling}, 270.0f, {0, 1, 0}, m_pixeldata[WALL_UP].color);
                    }
                }

                if(wcolor_xr != sf::Color::White)
                {
                    if(skip[WALL_RIGHT - 1])
                    {
                        skip[WALL_RIGHT - 1] = false;
                    }
                    else
                    {
                        BasicRenderer::draw_sprite(textures.at(m_pixeldata[WALL_DOWN].texture).id(),
                                              {m_tex_size * i * xz_scaling + m_tex_size / 2 + (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - m_tex_size / 2 : 0),
                                              y_scaling * m_tex_size / 2 - m_tex_size / 2, m_tex_size * j * xz_scaling + m_tex_size / 2 - m_tex_size / 2},
                                              {m_tex_size * xz_scaling, m_tex_size * y_scaling}, 90.0f, {0, 1, 0}, m_pixeldata[WALL_DOWN].color);
                    }
                }

                if(wcolor_yl != sf::Color::White)
                {
                    if(skip[WALL_UP - 1])
                    {
                        skip[WALL_UP - 1] = false;
                    }
                    else
                    {
                        BasicRenderer::draw_sprite(textures.at(m_pixeldata[WALL_LEFT].texture).id(),
                                              {m_tex_size * i * xz_scaling, y_scaling * m_tex_size / 2 - m_tex_size / 2, m_tex_size * j * xz_scaling - m_tex_size / 2 -
                                              (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - m_tex_size / 2 : 0)},
                                              {m_tex_size * xz_scaling, m_tex_size * y_scaling}, 180.0f, {0, 1, 0}, m_pixeldata[WALL_LEFT].color);
                    }
                }
                
                if(wcolor_yr != sf::Color::White)
                {
                    if(skip[WALL_DOWN - 1])
                    {
                        skip[WALL_DOWN - 1] = false;
                    }
                    else
                    {
                        BasicRenderer::draw_sprite(textures.at(m_pixeldata[WALL_RIGHT].texture).id(),
                                              {m_tex_size * i * xz_scaling, y_scaling * m_tex_size / 2 - m_tex_size / 2, m_tex_size * j * xz_scaling + m_tex_size / 2 +
                                              (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - m_tex_size / 2 : 0)},
                                              {m_tex_size * xz_scaling, m_tex_size * y_scaling}, 0.0f, {0, 1, 0}, m_pixeldata[WALL_RIGHT].color);
                    }
                }
            }
        }
    }
}

void ImageDrawer::render_cubes(const std::unordered_map<int, GLTexture>& textures, const Level& lvl, GLProgram& program)
{
    BasicRenderer::set_program(program);

    int i = 0, j = 0;
    for(const auto& color : level_pixel_colors)
    {
        if(color == sf::Color::Black)
        {
            //Walls
            BasicRenderer::draw_cube(textures.at(METAL_CUBE).id(),
            {scaled_tex_size_xz * i + m_tex_size / 2, scaled_tex_size_y / 2 - (m_tex_size + m_cf_height) / 2, scaled_tex_size_xz * j + m_tex_size / 2},
            {scaled_tex_size_xz, scaled_tex_size_y, scaled_tex_size_xz}, 0.0f, {0, 1, 0}, WHITE);
        }
        else if(color == sf::Color::White || color == sf::Color(192, 192, 192, 255))
        {
            //Floor
            BasicRenderer::draw_cube(textures.at(m_pixeldata[FLOOR].texture).id(),
            {scaled_tex_size_xz * i + m_tex_size / 2, -m_cf_height * 2, scaled_tex_size_xz * j + m_tex_size / 2},
            {scaled_tex_size_xz, m_cf_height, scaled_tex_size_xz}, 0.0f, {1, 0, 0},
                                        m_pixeldata[FLOOR].color);


            //Ceiling
            BasicRenderer::draw_cube(textures.at(m_pixeldata[CEILING].texture).id(),
            {scaled_tex_size_xz * i + m_tex_size / 2, scaled_tex_size_y - m_cf_height, scaled_tex_size_xz * j + m_tex_size / 2},
            {scaled_tex_size_xz, -m_cf_height, scaled_tex_size_xz}, maths::PI, {1, 0, 0},
                                        m_pixeldata[CEILING].color);
        }
        if(++j % level_height == 0) 
        {
            ++i;
            j = 0;
        }
    }
}

int ImageDrawer::get_cf_height() const
{
    return m_cf_height;
}