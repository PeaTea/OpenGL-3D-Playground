#include "Collision.h"

bool Collision::in_level(const Level& level, const glm::vec3& new_pos, const glm::vec3& old_pos)
{
    static Vec2 texture_size = level.scaled_tex_size();
    for(int i = 0; i < level.width(); i++)
    {	
        for(int j = 0; j < level.height(); j++)
        {
            float down_z = (new_pos.z + 1 + texture_size.x / 2) / texture_size.x;    // z-position(pixel) for walking down
            float up_z = (new_pos.z - 1 + texture_size.x / 2) / texture_size.x;      // z-position(pixel) for walking up
            
            if(level.get_pixel((new_pos.x + texture_size.x / 2) / texture_size.x,
                               ((old_pos.z < new_pos.z) ? down_z : up_z)) == sf::Color::Black)
            {
                return false;
            }
        }
    }
    return true;
}