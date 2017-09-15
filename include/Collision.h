#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include "Level.h"

class Collision
{
public:
	static glm::vec3 in_level(const Level& level, const glm::vec2& texture_size, glm::vec3& camera_pos);
};

#endif