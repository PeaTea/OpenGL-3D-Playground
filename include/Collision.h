#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include "Level.h"

class Collision
{
public:
	static bool in_level(const Level& level, const glm::vec2& texture_size, const glm::vec3& new_pos, const glm::vec3& old_pos);
};

#endif