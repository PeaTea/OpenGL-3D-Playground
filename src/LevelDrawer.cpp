#include "LevelDrawer.h"
#include "RenderGame.h"
#include "Maths.h"

using RG_GB::TEX_SIZE;

/*
===============	Level notes	==============
levels[0] = Tutorial:
Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

#define WALL_TEXTURE METAL_CUBE
#define FLOOR_TEXTURE MARBLE
#define CEILING_TEXTURE STONE

const glm::vec4 WHITE(1, 1, 1, 1);
const glm::vec4 GREY(0.5, 0.5, 0.5, 1);
const glm::vec4 LIGHT_GREY(0.75, 0.75, 0.75, 1);

void LevelDrawer::render(std::vector<GLTexture>& textures, const Level& lvl)
{
    for(unsigned int i = 0; i < lvl.width(); i++)
    {
        for(unsigned int j = 0; j < lvl.height(); j++)
        {
            sf::Color color = lvl.get_pixel(i, j);
            sf::Color wcolor_xl = lvl.get_pixel(i, (j == 0) ? j : j - 1);                       //Wall Color x left
            sf::Color wcolor_xr = lvl.get_pixel(i, (j + 1 == lvl.height()) ? j : j + 1);        //Wall Color x right
            sf::Color wcolor_yl = lvl.get_pixel((i == 0) ? i : i - 1, j);                       //Wall Color y left
            sf::Color wcolor_yr = lvl.get_pixel((i + 1 == lvl.width()) ? i : i + 1, j);         //Wall Color y right

            float xz_scaling = lvl.scaling().x;
            float y_scaling = lvl.scaling().y;

            if(color == sf::Color::White)
            {
                //Floor
                Renderer::draw_sprite(textures[FLOOR_TEXTURE].id(),
                                      {TEX_SIZE.x * i * xz_scaling, -TEX_SIZE.x / 2, TEX_SIZE.y * j * xz_scaling},
                                      TEX_SIZE * xz_scaling, 90.0f, {1, 0, 0}, WHITE);

                //Walls 
                if(wcolor_xl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          {TEX_SIZE.x * i * xz_scaling, y_scaling * TEX_SIZE.y / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j * xz_scaling - TEX_SIZE.x / 2 - (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE.x / 2 : 0)},
                                          {TEX_SIZE.x * xz_scaling, TEX_SIZE.y * y_scaling}, 180.0f, {0, 1, 0}, LIGHT_GREY);

                if(wcolor_xr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          {TEX_SIZE.x * i * xz_scaling, y_scaling * TEX_SIZE.y / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j * xz_scaling + TEX_SIZE.x / 2 + (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE.x / 2 : 0)},
                                          {TEX_SIZE.x * xz_scaling, TEX_SIZE.y * y_scaling}, 0.0f, {1, 0, 0}, LIGHT_GREY);

                if(wcolor_yl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          {TEX_SIZE.x * i * xz_scaling - TEX_SIZE.x / 2 - (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE.x / 2 : 0), y_scaling * TEX_SIZE.y / 2 - TEX_SIZE.x / 2,
                                          TEX_SIZE.y * j * xz_scaling + TEX_SIZE.y / 2 - TEX_SIZE.x / 2},
                                          {TEX_SIZE.x * xz_scaling, TEX_SIZE.y * y_scaling}, 270.0f, {0, 1, 0}, LIGHT_GREY);

                if(wcolor_yr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          {TEX_SIZE.x * i * xz_scaling + TEX_SIZE.x / 2 + (xz_scaling > 1 ? (lvl.scaled_tex_size().x / 2) - TEX_SIZE.x / 2 : 0), y_scaling * TEX_SIZE.y / 2 - TEX_SIZE.x / 2,
                                          TEX_SIZE.y * j * xz_scaling + TEX_SIZE.y / 2 - TEX_SIZE.x / 2},
                                          {TEX_SIZE.x * xz_scaling, TEX_SIZE.y * y_scaling}, 90.0f, {0, 1, 0}, LIGHT_GREY);

                //Ceiling
                Renderer::draw_sprite(textures[CEILING_TEXTURE].id(),
                                      {TEX_SIZE.x * i * xz_scaling, y_scaling  * TEX_SIZE.y - TEX_SIZE.y / 2, TEX_SIZE.y * j * xz_scaling},
                                      TEX_SIZE * xz_scaling, 270.0f, glm::vec3(1, 0, 0), GREY);
            }
        }
    }
}