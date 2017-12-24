#include "Collision.h"

bool Collision::in_level(const Level& level, const glm::vec2& texture_size, const glm::vec3& new_pos, const glm::vec3& old_pos)
{
    for(int i = 0; i < level.width(); i++)
    {	
        for(int j = 0; j < level.height(); j++)
        {
            if(new_pos.x < 0 || new_pos.z < 0)
            {
                return false;
            }
            
            float down_z = (new_pos.z + texture_size.y / 6.0f) / texture_size.y;    // z-position(pixel) for walking down
            float up_z = (new_pos.z + texture_size.y / 6.6f) / texture_size.y;      // z-position(pixel) for walking up

            if(level.get_pixel((new_pos.x + texture_size.x / 2) / texture_size.x,
                               ((old_pos.z < new_pos.z) ? down_z : up_z)) == sf::Color::Black)
            {
                return false;
            }
        }
    }
    return true;
}