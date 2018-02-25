#include "Collision.h"
#include "OutUtils.h"

/*
bool Collision::in_level(const Level& level, const glm::vec3& new_pos, const glm::vec3& old_pos)
{
    static Vec2<float> texture_size = level.scaled_tex_size();
    for(int i = 0; i < level.width(); i++)
    {	
        for(int j = 0; j < level.height(); j++)
        {
            float x = new_pos.x + texture_size.x / 2;
            float z = new_pos.z + texture_size.x / 2;
            if(x - 1 < 0 || x + 2 > level.width() * texture_size.x || z - 1 < 0 || z + 2 > level.height() * texture_size.x)
                return false;

            int down_z  = (int)((new_pos.z + 1 + texture_size.x / 2) / texture_size.x);   // z-position(pixel) for walking down
            int up_z    = (int)((new_pos.z - 1 + texture_size.x / 2) / texture_size.x);   // z-position(pixel) for walking up

            sf::Color final_color = level.get_pixel((int)((new_pos.x + texture_size.x / 2) / texture_size.x),
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
*/

glm::vec3 Collision::in_level(const Level& level, glm::vec3& new_pos, Camera& camera)
{
    static Vec2<float> texture_size = level.scaled_tex_size();

    glm::vec3 check_pos = new_pos;
    check_pos.z = check_pos.z + (check_pos.z > camera.position.z ? 2 : -1);
    check_pos.x = check_pos.x + (check_pos.x > camera.position.x ? 2 : -1);

    glm::vec2 cam_pos = camera.get_2D_pixel_pos(texture_size, check_pos);
    sf::Color pixel = level.get_pixel(cam_pos.x, cam_pos.y);

    if(pixel == sf::Color::Black || pixel == sf::Color(255, 255, 255, 0))
    {
        return camera.position;
    }
    return new_pos;
}