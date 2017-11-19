#include "Level.h"
#include <iostream>
#include "RenderGame.h"
#include <random>
#include <ctime>

/*
===============	Level notes	==============
levels[0] = Tutorial:
    Starting Positions:	-2000.0f, PlayerSize / 2, 44.0f
*/


#define WALL_TEXTURE MARBLE
#define FLOOR_TEXTURE LAVA
#define CEILING_TEXTURE STONE

const glm::vec4 WALL_COLOR(1, 1, 1, 1);
const glm::vec4 FLOOR_COLOR(0.3f, 0.3f, 1.0f, 1);
//const glm::vec4 FLOOR_COLOR(1, 1, 1, 1);
const glm::vec4 CEILING_COLOR(1, 1, 1, 1);

const float PLAYER_SIZE = 128.0f;

Level::Level(int width, int height)
    : width{width}
    , height{height}
{
}

Level::Level(const std::string& path)
{
    if(!image.loadFromFile(path))
    {
        std::cout << "Could not load file: " << path << std::endl;
    }

    width = image.getSize().x;
    height = image.getSize().y;
}

Level::~Level()
{
}


int Level::get_width() const
{
    return width;
}

int Level::get_height() const
{
    return height;
}

const unsigned char* Level::get_data()
{
    return image.getPixelsPtr();
}

sf::Color Level::get_pixel(unsigned int x, unsigned int y) const
{
    return image.getPixel(x, y);
}


void Level::draw(std::vector<GLTexture>& textures)
{
    for(unsigned int i = 0; i < width; i++)
    {	for(unsigned int j = 0; j < height; j++)
        {
            sf::Color color = image.getPixel(i, j);
            sf::Color wcolor_xl = image.getPixel(i, (j == 0) ? j : j - 1);			//Wall Color x left
            sf::Color wcolor_xr = image.getPixel(i, (j + 1 == height) ? j : j + 1);	//Wall Color x right
            sf::Color wcolor_yl = image.getPixel((i == 0) ? i : i - 1, j);			//Wall Color y left
            sf::Color wcolor_yr = image.getPixel((i + 1 == width) ? i : i + 1, j);	//Wall Color y right

            if(color == sf::Color::White)
            {
                //Floor
                Renderer::draw_sprite(textures[FLOOR_TEXTURE].id(),
                                      glm::vec3(RG_GB::TEX_SIZE.x * i, -PLAYER_SIZE / 2, RG_GB::TEX_SIZE.y * j + 44.0f),
                                      RG_GB::TEX_SIZE, 90.0f, glm::vec3(1, 0, 0), FLOOR_COLOR);

                //Ceiling
                Renderer::draw_sprite(textures[CEILING_TEXTURE].id(),
                                      glm::vec3(RG_GB::TEX_SIZE.x * i, PLAYER_SIZE / 2, RG_GB::TEX_SIZE.y * j + 44.0f),
                                      RG_GB::TEX_SIZE, 270.0f, glm::vec3(1, 0, 0), CEILING_COLOR);

                //Walls 
                if(wcolor_xl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(RG_GB::TEX_SIZE.x * i, 0, RG_GB::TEX_SIZE.y * j + 44.0f - RG_GB::TEX_SIZE.x / 2),
                                          RG_GB::TEX_SIZE, 180.0f, glm::vec3(0, 1, 0), WALL_COLOR);

                if(wcolor_xr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(RG_GB::TEX_SIZE.x * i, 0, RG_GB::TEX_SIZE.y * j - (-44.0f - RG_GB::TEX_SIZE.x) - RG_GB::TEX_SIZE.x / 2),
                                          RG_GB::TEX_SIZE, 0.0f, glm::vec3(1, 0, 0), WALL_COLOR);
                
                if(wcolor_yl == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(RG_GB::TEX_SIZE.x * i - RG_GB::TEX_SIZE.x / 2, 0, RG_GB::TEX_SIZE.y * j - (-44.0f - RG_GB::TEX_SIZE.y / 2) - RG_GB::TEX_SIZE.x / 2),
                                          RG_GB::TEX_SIZE, 270.0f, glm::vec3(0, 1, 0), WALL_COLOR);

                if(wcolor_yr == sf::Color::Black)
                    Renderer::draw_sprite(textures[WALL_TEXTURE].id(),
                                          glm::vec3(RG_GB::TEX_SIZE.x * i + RG_GB::TEX_SIZE.x / 2, 0, RG_GB::TEX_SIZE.y * j - (-44.0f - RG_GB::TEX_SIZE.y / 2) - RG_GB::TEX_SIZE.x / 2),
                                          RG_GB::TEX_SIZE, 90.0f, glm::vec3(0, 1, 0), WALL_COLOR);

                //END
            }
        }
        //std::cout << std::endl;
    }
}