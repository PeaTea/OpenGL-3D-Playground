#include "LevelDrawer.h"
#include "RenderGame.h"

using RG_GB::TEX_SIZE;

/*
===============	Level notes	==============
levels[0] = Tutorial:
Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/

#define WALL_TEXTURE MARBLE
#define FLOOR_TEXTURE METAL_CUBE
#define CEILING_TEXTURE STONE

const glm::vec4 WHITE(1, 1, 1, 1);

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

            float scaled_size = TEX_SIZE.y * lvl.wall_scaling();

            if(color == sf::Color::White)
            {
                //Floor
                Renderer::draw_sprite(textures[FLOOR_TEXTURE].id(),
                                      glm::vec3(TEX_SIZE.x * i, -TEX_SIZE.x / 2, TEX_SIZE.y * j + 44.0f),
                                      TEX_SIZE, 90.0f, glm::vec3(1, 0, 0), WHITE);

                //Walls 
                if(wcolor_xl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(TEX_SIZE.x * i, scaled_size / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j + 44.0f - TEX_SIZE.x / 2),
                                          glm::vec2(TEX_SIZE.x, scaled_size), 180.0f, glm::vec3(0, 1, 0), WHITE);

                if(wcolor_xr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(TEX_SIZE.x * i, scaled_size / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j - (-44.0f - TEX_SIZE.x) - TEX_SIZE.x / 2),
                                          glm::vec2(TEX_SIZE.x, scaled_size), 0.0f, glm::vec3(1, 0, 0), WHITE);

                if(wcolor_yl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(TEX_SIZE.x * i - TEX_SIZE.x / 2, scaled_size / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j - (-44.0f - TEX_SIZE.y / 2) - TEX_SIZE.x / 2),
                                          glm::vec2(TEX_SIZE.x, scaled_size), 270.0f, glm::vec3(0, 1, 0), WHITE);

                if(wcolor_yr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(TEX_SIZE.x * i + TEX_SIZE.x / 2, scaled_size / 2 - TEX_SIZE.x / 2, TEX_SIZE.y * j - (-44.0f - TEX_SIZE.y / 2) - TEX_SIZE.x / 2),
                                          glm::vec2(TEX_SIZE.x, scaled_size), 90.0f, glm::vec3(0, 1, 0), WHITE);

                //Ceiling
                Renderer::draw_sprite(textures[CEILING_TEXTURE].id(),
                                      glm::vec3(TEX_SIZE.x * i, scaled_size - TEX_SIZE.y / 2, TEX_SIZE.y * j + 44.0f),
                                      TEX_SIZE, 270.0f, glm::vec3(1, 0, 0), WHITE);
            }
        }
    }
}