#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include "Level.h"

struct Collision
{
    static bool in_level(const Level& level, const glm::vec3& new_pos, const glm::vec3& old_pos);
};

#endif