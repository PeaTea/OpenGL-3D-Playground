#include "Collision.h"

/*
	Somewhat working - still some camera issues.
	TODO: Make it better!
*/

bool Collision::in_level(const Level& level, const glm::vec2& texture_size, glm::vec3& new_pos)
{
	for(int i = 0; i < level.get_width(); i++)
	{	
		for(int j = 0; j < level.get_height(); j++)
		{
			if(new_pos.x < 0 || new_pos.z < 0)
			{
				return false;
			}

			if(level.get_pixel((new_pos.x + texture_size.x / 2) / texture_size.x,
							   (new_pos.z + texture_size.y / 6.42f) / texture_size.y) == sf::Color::Black)
			{
				return false;
			}
		}
	}
	return true;
}