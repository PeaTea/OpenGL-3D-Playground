#include "LevelDrawer.h"
#include "RenderGame.h"
#include "Maths.h"

/*
===============	Level notes	==============
levels[0] = Tutorial:
Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

#define TEX_SIZE Settings::tex_size()

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

LevelDrawer::LevelDrawer()
{
    m_pixeldata[(int)PixelID::FLOOR].texture = MARBLE;
    m_pixeldata[(int)PixelID::FLOOR].color = LIGHT_GREY;

    m_pixeldata[(int)PixelID::CEILING].texture = MARBLE;
    m_pixeldata[(int)PixelID::CEILING].color = DARK_GREY;
}

void LevelDrawer::render(std::vector<GLTexture>& textures, const Level& lvl, GLProgram& program)
{
    Renderer::set_program(program);
    for(unsigned int i = 0; i < lvl.width(); i++)
    {
        for(unsigned int j = 0; j < lvl.height(); j++)
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
                Renderer::draw_sprite(textures[m_pixeldata[FLOOR].texture].id(),
                                      {TEX_SIZE * i * xz_scaling, -TEX_SIZE / 2, TEX_SIZE * j * xz_scaling},
                                      TEX_SIZE * xz_scaling, 90.0f, {1, 0, 0}, m_pixeldata[FLOOR].color);

                
                //Ceiling
                Renderer::draw_sprite(textures[m_pixeldata[CEILING].texture].id(),
                                      {TEX_SIZE * i * xz_scaling, y_scaling  * TEX_SIZE - TEX_SIZE / 2, TEX_SIZE * j * xz_scaling},
                                      TEX_SIZE * xz_scaling, 270.0f, glm::vec3(1, 0, 0), m_pixeldata[CEILING].color);
                
                //Walls 
                if(wcolor_xl != sf::Color::White)
                {
                    if(skip[WALL_LEFT - 1])
                    {
                        skip[WALL_LEFT - 1] = false;
                    }
                    else
                    {
                        Renderer::draw_sprite(textures[m_pixeldata[WALL_UP].texture].id(),
                                              {TEX_SIZE * i * xz_scaling - TEX_SIZE / 2 - (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE / 2 : 0),
                                              y_scaling * TEX_SIZE / 2 - TEX_SIZE / 2, TEX_SIZE * j * xz_scaling + TEX_SIZE / 2 - TEX_SIZE / 2},
                                              {TEX_SIZE * xz_scaling, TEX_SIZE * y_scaling}, 270.0f, {0, 1, 0}, m_pixeldata[WALL_UP].color);
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
                        Renderer::draw_sprite(textures[m_pixeldata[WALL_DOWN].texture].id(),
                                              {TEX_SIZE * i * xz_scaling + TEX_SIZE / 2 + (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE / 2 : 0),
                                              y_scaling * TEX_SIZE / 2 - TEX_SIZE / 2, TEX_SIZE * j * xz_scaling + TEX_SIZE / 2 - TEX_SIZE / 2},
                                              {TEX_SIZE * xz_scaling, TEX_SIZE * y_scaling}, 90.0f, {0, 1, 0}, m_pixeldata[WALL_DOWN].color);
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
                        Renderer::draw_sprite(textures[m_pixeldata[WALL_LEFT].texture].id(),
                                              {TEX_SIZE * i * xz_scaling, y_scaling * TEX_SIZE / 2 - TEX_SIZE / 2, TEX_SIZE * j * xz_scaling - TEX_SIZE / 2 -
                                              (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE / 2 : 0)},
                                              {TEX_SIZE * xz_scaling, TEX_SIZE * y_scaling}, 180.0f, {0, 1, 0}, m_pixeldata[WALL_LEFT].color);
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
                        Renderer::draw_sprite(textures[m_pixeldata[WALL_RIGHT].texture].id(),
                                              {TEX_SIZE * i * xz_scaling, y_scaling * TEX_SIZE / 2 - TEX_SIZE / 2, TEX_SIZE * j * xz_scaling + TEX_SIZE / 2 +
                                              (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE / 2 : 0)},
                                              {TEX_SIZE * xz_scaling, TEX_SIZE * y_scaling}, 0.0f, {0, 1, 0}, m_pixeldata[WALL_RIGHT].color);
                    }
                }
            }
        }
    }
}