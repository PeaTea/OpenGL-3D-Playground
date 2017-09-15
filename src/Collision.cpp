#include "Collision.h"

glm::vec3 Collision::in_level(const Level& level, const glm::vec2& texture_size, glm::vec3& camera_pos)
{
	for(int i = 0; i < level.get_width(); i++)
	{	
		for(int j = 0; j < level.get_height(); j++)
		{
			if(level.get_pixel(i, j) == sf::Color::White)
			{
				if(camera_pos.x > i * texture_size.x && camera_pos.x < (i + 1) * texture_size.x)
				{
					if(camera_pos.z > j * texture_size.y && camera_pos.z < (j + 1) * texture_size.y)
					{
						camera_pos.x -= 1;
						camera_pos.z -= 1;
						return glm::vec3(0, 1, 0);
					}
				}
			}
		}
	}
	return glm::vec3(1, 1, 1);
}