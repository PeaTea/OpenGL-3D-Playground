#include "Collision.h"

bool Collision::in_level(const Level& level, const glm::vec3& new_pos, const glm::vec3& old_pos)
{
    static Vec2 texture_size = level.scaled_tex_size();
    for(unsigned int i = 0; i < level.width(); i++)
    {	
        for(unsigned int j = 0; j < level.height(); j++)
        {
            float x = new_pos.x + texture_size.x / 2;
            float z = new_pos.z + texture_size.x / 2;
            if(x - 1 < 0 || x + 2 > level.width() * texture_size.x || z - 1 < 0 || z + 2 > level.height() * texture_size.x)
                return false;

            float down_z = (new_pos.z + 1 + texture_size.x / 2) / texture_size.x;    // z-position(pixel) for walking down
            float up_z = (new_pos.z - 1 + texture_size.x / 2) / texture_size.x;      // z-position(pixel) for walking up

            sf::Color final_color = level.get_pixel((new_pos.x + texture_size.x / 2) / texture_size.x,
                                                    ((old_pos.z < new_pos.z) ? down_z : up_z));
            
            if(final_color == sf::Color::Black ||
               final_color == sf::Color(255, 255, 255, 0))
            {
                return false;
            }
        }
    }
    return true;
}